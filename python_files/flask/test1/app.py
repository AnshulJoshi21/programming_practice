from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def home() -> str:
    return render_template("home.html")


@app.route("/about")
def about() -> str:
    return render_template("about.html")


@app.route("/contact")
def contact() -> str:
    return render_template("contact.html")


@app.route("/students")
def students() -> str:
    # students_list: list[str] = ["Suresh", "Ramesh", "Rajesh", "Rakesh", "Naresh"]
    students_list: list[str] = []
    is_admin: bool = True
    return render_template("students.html", students=students_list, admin_status=is_admin)


@app.route("/status")
def status() -> str:
    name: str = "Aman"
    logged_in: bool = True
    return render_template("status.html", username=name, status=logged_in)


if __name__ == "__main__":
    app.run(debug=True)
