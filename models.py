

class User:
    def __init__(self, id, name, email, salary, broker, sub):
        self.id = id
        self.name = name
        self.email = email
        self.salary = salary
        self.broker = broker
        self.sub = sub

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.name,
            "email": self.email,
            "salary": bool(self.salary),
            "broker": bool(self.broker),
            "sub": bool(self.sub),
        }

class AuthUser:
    def __init__(self, user, auth_token):
        self.user = user
        self.auth_token = auth_token

    def to_dict(self):
        return {
            "auth_token": self.auth_token,
            "user": self.user.to_dict()
        }


class Deposit:
    def __init__(self, id, name, desc, dur_min, dur_max, p_min, p_max, s_min, req_salary, req_broker, req_premium):
        self.id = id
        self.name = name
        self.description = desc
        self.dur_min = dur_min
        self.dur_max = dur_max
        self.p_min = p_min
        self.p_max = p_max
        self.s_min = s_min
        self.req_salary = req_salary
        self.req_broker = req_broker
        self.req_premium = req_premium

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.name,
            "description": self.description,
            "duration_min": self.dur_min,
            "duration_max": self.dur_max,
            "percent_min": self.p_min,
            "percent_max": self.p_max,
            "sum_min": self.s_min,
            "req_salary": bool(self.req_salary),
            "req_broker": bool(self.req_broker),
            "req_premium": bool(self.req_premium),
        }