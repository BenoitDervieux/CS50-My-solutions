import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if not name or not month or not day:
            return redirect("/")
        else:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        birthdays = db.execute("SELECT * from birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route('/delete', methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id=?", id)
    return redirect('/')

@app.route('/update_page', methods=["POST"])
def update_page():
    id = request.form.get("id")
    if id:
        person = db.execute("SELECT id, name, month, day FROM birthdays where id=?", id)
    return render_template('/update.html', person=person)



@app.route('/update_profile', methods=['POST'])
def update_profile():
    id = request.form.get("id")
    if request.method == "POST":
        new_name = request.form.get("name_update")
        new_month = request.form.get("month_update")
        new_day = request.form.get("day_update")
        if not new_name or not new_month or not new_day:
            return redirect("/")
        else:
            print(id)
            db.execute("UPDATE birthdays SET name=?, month=?, day=? WHERE id=?", new_name, new_month, new_day, id)

        return redirect("/")

