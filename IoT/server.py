# import flask
from flask import Flask, request
import utils.response as response
import utils.database as db

# create server
server = Flask(__name__)

@server.route("/welcome")
def welcome():
    return response.create_response("Welcome to IoT Application");

@server.route("/monitor", methods = {'GET', 'POST'})
def monitoring_methods():
    if (request.method == 'GET'):
        # to get data from database form a query
        query = f"select * from monitor;"

        # execute query to get all temps from database
        temps = db.execute_select_query(query)

        # return temps into response
        return response.create_response(temps)
    elif(request.method == 'POST'):
        # retrieve data from request body
        temperature = request.get_json().get('temperature')
        rain = request.get_json().get('rain')
        #if 1:
        query = f"insert into monitor(temperature,rain) values({temperature},{rain});"
        
        db.execute_query(query)

        # return some response to the client
        return response.create_response("data is added successfully")


# run server
server.run(host="0.0.0.0",port=5000,debug=True)
