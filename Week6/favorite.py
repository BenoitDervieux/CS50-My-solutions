import csv

from cs50 import SQL

db = SQL("sqlite://favorites.db")

title = input("Title: ").strip()

rows = db.execute("SELECT title AS counter FROM favorite WHERE title LIKE ?", title)

for row in rows:
    print(row["title"])