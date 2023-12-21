import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    symbol_db = db.execute("SELECT symbol FROM transactions WHERE user_id = ?", user_id)
    symbol = symbol_db[0]["symbol"]
    shares_db = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    shares = shares_db[0]["shares"]
    current_price_dict = lookup(symbol)
    current_price = current_price_dict["price"]

    db.execute("INSERT INTO transactions (total_value_holding) VALUES (?)", current_price*shares)

    stocks = db.execute("SELECT symbol, SUM(shares) AS shares, price, total_value_holding FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = round(cash_db[0]["cash"], 2)

    return render_template("index.html", stocks = stocks, cash = cash)
    # number of shares of each stock
    # current price of each stock (use lookup)
    # total value of each holding
    # user's current cash balance
    # total value of stocks and cash together


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)

        # symbol input
        if not symbol:
            return apology("Input a symbol.")
        elif stock == None:
            return apology("Symbol doesn't exist.")

        # number of shares input
        if shares <= 0:
            return apology("Invalid number of shares.")

        user_id = session["user_id"]
        user_cash_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_dict[0]["cash"]
        transaction_total = shares*stock["price"]
        if transaction_total > user_cash:
            return apology("You don't have enough cash.")
        else:
            updated_cash = user_cash - transaction_total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)
            date = datetime.datetime.now()
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], date)
            flash("Bought!")
            return redirect("/")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    """Get stock quote."""
    symbol = request.form.get("symbol")

    if request.method == "POST":
        stock = lookup(symbol)
        price = stock["price"]
        name = stock["name"]
        return render_template("quoted.html", name=name, symbol=symbol, price=usd(price))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")
    if request.method == "POST":
        # if any field is blank, return apology
        if not username or not password or not confirmation:
            return apology("Fill in all blank fields.")
        # if password and confirmation don't match, return apology
        elif password != confirmation:
            return apology("Passwords don't match.")

        hash = generate_password_hash(password)

        # insert new user into users table
        # if username is already taken, return apology
        try:
            new_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        except:
            return apology("Username taken.")

        # remember current user
        session["user_id"] = new_user
        # log user in
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
