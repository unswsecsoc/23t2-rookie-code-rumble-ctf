FROM python:3.10-alpine

WORKDIR /app

COPY requirements.txt /app
RUN pip install -r requirements.txt

COPY app /app

EXPOSE 3000

CMD ["python3", "app.py"]