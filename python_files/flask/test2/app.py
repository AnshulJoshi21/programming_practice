from flask import Flask, request, render_template

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def index() -> str:
    if request.method == "POST":
        name: str = request.form.get("username", "").strip() or "anonymous"
        return render_template("result.html", name=name)

    return render_template("form.html")


if __name__ == "__main__":
    app.run(debug=True)
