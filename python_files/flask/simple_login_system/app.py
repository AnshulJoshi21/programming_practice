from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def home() -> str:
    result: str | None = None

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username == "admin" and password == "1234":
            result = "login successful"
        else:
            result = "login failed"

    return render_template("form.html", result=result)


if __name__ == "__main__":
    app.run(debug=True)
