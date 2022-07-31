import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == 'POST':
        return redirect("/index.html")
    if request.method == "GET":
        db.execute("create table if not exists transactions (transac_id int not null, symbol varchar(60) not null, number_of_stock int not null, price_stock int not null, date_and_time not null, user_id int not null, primary key(transac_id), foreign key(user_id) references users(id))")
        db.execute("create table if not exists stocks (symbol varchar(10) not null, name varchar(60) not null, quantity int not null, user_id int not null, primary key(symbol), foreign key(user_id) references users(id))")
        stonks = db.execute("select * from stocks where user_id= ?", session["user_id"])
        biege = {}
        total_stock = 0
        for x in stonks:
            look = lookup(x['symbol'])
            biege[x['symbol']] = look['price']
            total_stock += look['price'] * x['quantity']
        cash = db.execute("select cash from users where id = ?", session["user_id"])

        return render_template("/index.html", stonks=stonks, biege=biege, cash=cash, total_stock=total_stock)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

        if request.method == "GET":
            return render_template("/buy.html")
        if request.method == 'POST':
            quote = request.form.get("symbol")
            if (quote == "Nein"):
                return apology("You need to select a stock", 400)
            quote = lookup(quote)
            print("Allé c'est aprti on va imprimer la quote")
            print(quote)
            if (quote == None):
                return render_template("/buy.html"), 400
            quantity = request.form.get("shares")
            try:
                quantity = int(quantity)
                if (quantity < 0 ):
                    return render_template("/buy.html"), 400
            except ValueError:
                return render_template("/buy.html"), 400
            print(type(quantity))
            if (quantity == 0):
                return apology("You need to select a quantity", 400)
            quantity = float(request.form.get("shares"))
            total = quote['price'] * quantity

            if (quote == None):
                return apology("invalid symbol", 400)
            if not quote or not quantity:
                return apology("You missed a field!", 403)

            budget = db.execute("select cash from users where id = ?", session["user_id"])

            if (budget[0]['cash'] >= total):
                #db.execute("drop table transactions")
                #db.execute("drop table stocks")
                db.execute("create table if not exists transactions (transac_id int not null, symbol varchar(60) not null, number_of_stock int not null, price_stock int not null, date_and_time not null, user_id int not null, primary key(transac_id), foreign key(user_id) references users(id))")
                db.execute("create table if not exists stocks (symbol varchar(10) not null, name varchar(60) not null, quantity int not null, user_id int not null, primary key(symbol), foreign key(user_id) references users(id))")
                n_transaction = db.execute("select count(transac_id) from transactions")
                n_transaction = n_transaction[0]['count(transac_id)'] + 1
                db.execute("insert into transactions (transac_id, symbol, number_of_stock, price_stock, date_and_time, user_id) values (?,?,?,?,datetime(),?)", n_transaction, quote['symbol'], quantity, quote['price'], session["user_id"] )
                new_budget = budget[0]['cash'] - total
                db.execute("update users set cash=? where id=?", new_budget, session["user_id"])

                check = db.execute("select distinct symbol from stocks where symbol=?", quote['symbol'])
                if (check == []):
                    db.execute("insert into stocks (symbol, name, quantity, user_id) values (?,?,?,?)", quote['symbol'], quote['name'], quantity, session["user_id"])
                    return redirect("/")
                else:
                    if (check[0]['symbol'] == quote['symbol']):
                        update_quantity = db.execute("select distinct quantity from stocks where symbol=?", quote['symbol'])
                        update_quantity = update_quantity[0]['quantity'] + quantity
                        db.execute("update stocks set quantity=? where symbol=?", update_quantity, quote['symbol'])


                        return redirect("/")
            else:
                return redirect("/")





@app.route("/history", methods=['GET'])
@login_required
def history():
    if request.method == 'GET':
        histories = db.execute("select symbol, number_of_stock, price_stock, date_and_time from transactions where user_id=? order by date_and_time desc", session["user_id"])
        return render_template("history.html", histories=histories)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == 'POST':
        quote = request.form.get('symbol')
        if (len(quote) == 0):
            return render_template("quote.html"), 400
        quote = lookup(quote)
        print("On va imprimer la quote")
        print(quote)
        if (quote == None):
            return render_template("quote.html"), 400
        return render_template('/quoted.html', quote=quote)
    if request.method == 'GET':
        return render_template("quote.html")

@app.route("/quoted", methods=["GET", "POST"])
@login_required
def quoted():
    if request.method == 'POST':
        quote = request.form.get('symbol')
        if (len(quote) == 0):
            return render_template("quote.html"), 400
        quote = lookup(quote)
        print("On va imprimer la quote")
        print(quote)
        if (quote == None):
            return render_template("quote.html"), 400
        return render_template('/quoted.html', quote=quote)
    if request.method == 'GET':
        return render_template('/quoted.html')




@app.route("/register", methods=["GET", "POST"])
def register():

    session.clear()


    if request.method == "POST":
        username = request.form.get("username")
        password1 = request.form.get("password")
        password2 = request.form.get("confirmation")
        password_hashed = generate_password_hash(password1, method='pbkdf2:sha256', salt_length=8)

        test_password = db.execute("select users.id from users where username=?", username)

        try:
            if (test_password[0]['id'] != None):
                return apology("This name is already taken", 400)

        except (KeyError, TypeError, ValueError, IndexError):

            if not username or not password1 or not password2:
                return apology("You missed a field!", 400)
            if (password1 != password2):
                return apology("Passwords are not the same", 400)
            else:
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hashed)

                rows = db.execute("select * from users where username = ?", username)

                session["user_id"] = rows[0]["id"]

                return redirect("/")

    else:
        return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        print("Symbole kulkavekira")
        print(symbol)
        quantity_to_sell = request.form.get('shares')

        if (symbol == None):
            return apology("You need to select a stock", 400)
        if not quantity_to_sell:
            return apology("You need to select a number of shares", 400)
        quantity_detained = db.execute("select quantity from stocks where symbol=? and user_id=?", symbol, session["user_id"])

        if (int(quantity_to_sell) > int(quantity_detained[0]['quantity'])):
            return apology("You don't have enough stock to sell", 400)
        if (int(quantity_to_sell) == int(quantity_detained[0]['quantity'])):
            info_stock = lookup(symbol)
            price = float(info_stock['price']) * int(quantity_to_sell)
            #update le cash - get le cash et update le
            cash = db.execute("select cash from users where id=?", session["user_id"])
            new_cash = int(cash[0]['cash']) + price
            db.execute("update users set cash=? where id=?", new_cash, session["user_id"])
            #update le stock d'actions
            db.execute("delete from stocks where symbol=?", symbol)
            #update transaction
            n_transaction = db.execute("select count(transac_id) from transactions")
            n_transaction = n_transaction[0]['count(transac_id)'] + 1
            db.execute("insert into transactions (transac_id, symbol, number_of_stock, price_stock, date_and_time, user_id) values (?,?,?,?,datetime(),?)", n_transaction, info_stock['symbol'], quantity_to_sell, info_stock['price'], session["user_id"] )
            return redirect("/")
        else:
            info_stock = lookup(symbol)
            price = float(info_stock['price']) * int(quantity_to_sell)
            #update le cash - get le cash et update le
            cash = db.execute("select cash from users where id=?", session["user_id"])
            new_cash = int(cash[0]['cash']) + price
            db.execute("update users set cash=? where id=?", new_cash, session["user_id"])
            #update le stock d'actions
            update_quantity = int(quantity_detained[0]['quantity']) - int(quantity_to_sell)
            db.execute("update stocks set quantity=? where user_id=? and symbol=?", update_quantity, session["user_id"], symbol)
            #update transaction
            n_transaction = db.execute("select count(transac_id) from transactions")
            n_transaction = n_transaction[0]['count(transac_id)'] + 1
            db.execute("insert into transactions (transac_id, symbol, number_of_stock, price_stock, date_and_time, user_id) values (?,?,?,?,datetime(),?)", n_transaction, info_stock['symbol'], -1*int(quantity_to_sell), -1*info_stock['price'], session["user_id"] )
            return redirect("/")

    if request.method == 'GET':
        db.execute("create table if not exists transactions (transac_id int not null, symbol varchar(60) not null, number_of_stock int not null, price_stock int not null, date_and_time not null, user_id int not null, primary key(transac_id), foreign key(user_id) references users(id))")
        db.execute("create table if not exists stocks (symbol varchar(10) not null, name varchar(60) not null, quantity int not null, user_id int not null, primary key(symbol), foreign key(user_id) references users(id))")

        stonks = db.execute("select * from stocks where user_id= ?", session["user_id"])
        return render_template("/sell.html", stonks=stonks)
