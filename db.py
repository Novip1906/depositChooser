import sqlite3
import config
class DB:
    def __init__(self, db_name):
        try:
            self.conn = sqlite3.connect(db_name)
            self.cur = self.conn.cursor()
            self.users = self._Users(self.conn)
        except sqlite3.Error as error:
            print("Ошибка при подключении к sqlite", error)


    class _Users:
        def __init__(self, conn):
            self.conn = conn
            self.cur = self.conn.cursor()



