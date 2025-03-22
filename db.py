import sqlite3
import config
import bcrypt
from models import User, Deposit

class DB:
    def __init__(self, db_name):
        try:
            self.conn = sqlite3.connect(db_name, check_same_thread=False)
            self.cur = self.conn.cursor()
            self.users = self._Users(self.conn)
            self.deposits = self._Deposits(self.conn)

            self.cur.execute('''
            CREATE TABLE IF NOT EXISTS deposits (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                description TEXT,
                percent_min REAL NOT NULL,
                percent_max REAL NOT NULL,
                duration_min INTEGER NOT NULL,
                duration_max INTEGER NOT NULL,
                sum_min INTEGER NOT NULL,
                req_salary BOOLEAN NOT NULL,
                req_broker BOOLEAN NOT NULL,
                req_premium BOOLEAN NOT NULL
            )''')

            self.cur.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                email TEXT NOT NULL,
                password TEXT NOT NULL,
                salary BOOLEAN NOT NULL DEFAULT 0,
                broker BOOLEAN NOT NULL DEFAULT 0,
                sub BOOLEAN NOT NULL DEFAULT 0
            )''')

            self.conn.commit()


        except sqlite3.Error as error:
            print("Ошибка при подключении к sqlite", error)


    class _Users:
        def __init__(self, conn):
            self.conn = conn
            self.cur = self.conn.cursor()

        def check_if_exists(self, email):
            self.cur.execute("SELECT * FROM users WHERE email=?", (email,))
            return len(self.cur.fetchall()) > 0

        def check_sign_in(self, email, password):
            self.cur.execute("SELECT password FROM users WHERE email=?", (email,))
            row = self.cur.fetchone()

            if row:
                stored_hashed_password = row[0].encode()
                return bcrypt.checkpw(password.encode(), stored_hashed_password)

            return False

        def add(self, email, name, password):
            self.cur.execute("INSERT INTO users (email, name, password) VALUES (?, ?, ?)", (email, name,
                                                                                            self.__hash_password(password)))
            self.conn.commit()
            self.cur.execute("SELECT * FROM users WHERE email=?", (email,))
            r = self.cur.fetchone()
            if r:
                return User(r[0], r[1], r[2], r[4], r[5], r[6])
            return None

        def get(self, email):
            self.cur.execute("SELECT * FROM users WHERE email=?", (email,))
            r = self.cur.fetchone()
            if r:
                return User(r[0], r[1], r[2], r[4], r[5], r[6])
            return None

        def update(self, email, name, salary, broker, subscription):
            self.cur.execute("UPDATE users SET name = ?, salary = ?, broker = ?, sub = ? WHERE email = ?", (name, salary, broker, subscription, email))
            self.conn.commit()

        def __hash_password(self, password):
            salt = bcrypt.gensalt()
            hashed = bcrypt.hashpw(password.encode(), salt)
            return hashed.decode()

    class _Deposits:
        def __init__(self, conn):
            self.conn = conn
            self.cur = self.conn.cursor()

        def get(self, dur_min, dur_max, p_min, p_max, sum_min, req_salary, req_broker, req_premium):
            self.cur.execute("SELECT * FROM deposits WHERE duration_min>=? AND duration_max<=? AND percent_min>=? AND percent_max<=? AND sum_min>=? AND req_salary>=? AND req_broker>=? AND req_premium>=?",
                             (dur_min, dur_max, p_min, p_max, sum_min, req_salary, req_broker, req_premium))
            return [Deposit(*d) for d in self.cur.fetchall()]

