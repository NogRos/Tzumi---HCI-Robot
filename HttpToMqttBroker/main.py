# # Set up Flask:
# from flask import Flask, request, jsonify
# from flask_cors import CORS
#
# from mqtt import connect_mqtt, send_mqtt_message
#
# app = Flask(__name__)
#
# # Set up Flask to bypass CORS:
# cors = CORS(app)
#
# # connection to MQTT #
# client = connect_mqtt()
# client.loop_start()
#
#
# ######################
#
#
# # Create the receiver API POST endpoint:
# @app.route("/receiver", methods=["POST"])
# def postME():
#     data = request.get_json()
#     some_text = data['some_text']
#
#     send_mqtt_message(client, some_text)
#
#
#     data = jsonify(data)
#     print("data is: ", data.data)
#     return data
#
#
# if __name__ == "__main__":
#     app.run(debug=True)

# Python 3 server example
from http.server import BaseHTTPRequestHandler, HTTPServer
import time

from mqtt import send_mqtt_message, connect_mqtt

hostName = "0.0.0.0"
serverPort = 8080

# connection to MQTT #
client = connect_mqtt()
client.loop_start()


class MyServer(BaseHTTPRequestHandler):
    counter = 0

    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title>https://pythonbasics.org</title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        self.wfile.write(bytes("<p>This is an example web server.</p>", "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
        print('message ')
        send_mqtt_message(client, '1')


if __name__ == "__main__":
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
