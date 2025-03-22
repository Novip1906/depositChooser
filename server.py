import config
from db import DB
from flask import Flask, request, jsonify
import models
from flask_jwt_extended import JWTManager, create_access_token, jwt_required, get_jwt_identity

db = DB(config.DB_FILENAME)

app = Flask(__name__)
app.config['JWT_SECRET_KEY'] = 'konspect'
jwt = JWTManager(app)

def create_response(code=0, data=None):
    return jsonify({
        "code": code,
        "data": [] if data is None else [d.to_dict() for d in data] if isinstance(data, list) else data.to_dict()
    })

@app.route("/sign_up", methods=['POST'])
def sign_up():
    data = request.get_json()
    if not data:
        return create_response(2)
    email, name, password = data.get("email"), data.get("name"), data.get("password")
    if db.users.check_if_exists(email):
        return create_response(1)
    user = db.users.add(email, name, password)
    access_token = create_access_token(identity=email)
    auth_user = models.AuthUser(user, access_token)
    return create_response(data=auth_user)

@app.route("/sign_in", methods=['POST'])
def sign_in():
    data = request.get_json()
    if not data:
        return create_response(2)
    email, password = data.get("email"), data.get("password")
    if db.users.check_sign_in(email, password):
        user = db.users.get(email)
        access_token = create_access_token(identity=email)
        auth_user = models.AuthUser(user, access_token)
        return create_response(data=auth_user)
    elif db.users.check_if_exists(email):
        return create_response(2)
    return create_response(1)

@app.route("/get_deposits", methods=['GET'])
def get_deposits():
    try:
        deposits = db.deposits.get(
            float(request.args.get("duration_min", 0)),
            float(request.args.get("duration_max", 36)),
            float(request.args.get("percent_min", 0)),
            float(request.args.get("percent_max", 1000)),
            int(request.args.get("sum_min", 0)),
            request.args.get("req_salary", "false").lower() == "true",
            request.args.get("req_broker", "false").lower() == "true",
            request.args.get("req_premium", "false").lower() == "true",
        )
        print(deposits)
        return create_response(data=deposits)
    except Exception as e:
        return create_response(code=1)

@app.route("/get_user", methods=['GET'])
@jwt_required()
def get_user():
    email = get_jwt_identity()
    user = db.users.get(email)

    if not user:
        return create_response(1)
    return create_response(data=user)


@app.route("/update_user", methods=['POST'])
@jwt_required()
def update_user():
    email = get_jwt_identity()
    user = db.users.get(email)

    if not user:
        return create_response(code=1)

    data = request.get_json()
    if not data:
        return create_response(code=2)

    name = data.get("name")
    salary = data.get("salary")
    broker = data.get("broker")
    subscription = data.get("sub")

    db.users.update(email, name, salary, broker, subscription)

    return create_response()

if __name__ == "__main__":
    app.run(debug=True)
