import json
from random import randint
from openai import InvalidRequestError

from chat import STARTER_PROMPT_LEN, get_chat_completions, get_starter_prompts
from exceptions import GenerationException
from flask import Flask, abort, flash, g, redirect, render_template, request, url_for

app = Flask(__name__)


@app.route("/")
def index():
    response = request.args.get("response")
    return render_template("index.html", response=response)


@app.route("/", methods=["POST"])
def chat():
    message = request.form.get("message")

    if message is None:
        abort(400, "missing message argument")

    conversation = get_starter_prompts("TEST", "Jim")
    message = {"role": "user", "content": message}
    conversation.append(message)
    print(conversation)
    try:
        conversation = get_chat_completions(conversation, "TEST")
    except GenerationException as e:
        conversation = None
        abort(500, str(e))
    except InvalidRequestError as e:
        conversation = None
        abort(
            500,
            f"Here's the exact error, but most likely your conversation has gotten too long: {e}",
        )

    if conversation is not None:
        print(
            json.dumps(
                {
                    "message": message,
                    "response": conversation[-3]
                    if conversation[-1]["role"] == "system"
                    else conversation[-1],
                    "data": conversation[-2]
                    if conversation[-1]["role"] == "system"
                    else None,
                }
            )
        )
    return render_template(
        "index.html", response=conversation[-1]["content"], debug=True
    )


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=3000)
