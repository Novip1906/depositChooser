import socket
import json
import config
from db import DB

actions = {}

def register_action(action_name):
    def decorator(func):
        actions[action_name] = func
        return func
    return decorator

def create_response(success: bool, message = ''):
    return {"status": "success" if success else "error", "message": message}



def handle_request(request):
    try:
        data = json.loads(request)
        action = data.get("action")
        if action in actions:
            response = actions[action](data)
        else:
            response = {"status": "error", "message": "Invalid action."}
    except Exception as e:
        response = {"status": "error", "message": str(e)}
    return json.dumps(response)


def start_server(host='127.0.0.1', port=65432):
    """Запуск сервера."""
    db = DB(config.DB_FILENAME)
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, addr = server_socket.accept()
        print(f"Connection from {addr}")
        request = client_socket.recv(1024).decode('utf-8')
        response = handle_request(request)
        client_socket.sendall(response.encode('utf-8'))
        client_socket.close()


if __name__ == "__main__":
    start_server()
