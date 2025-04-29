from flask import Flask, request, send_file, jsonify

app = Flask(__name__)

# endpoint para recibir la versión del cliente
@app.route("/get-version", methods=["POST"])
def get_version():
    client_version = request.json.get('version')
    print(f"Received version from ESP32: {client_version}")

    server_version = "1.9"
    print(f"Server current version: {server_version}")

    if not client_version:
        return jsonify({"error": "Missing 'version' parameter."}), 400

    if client_version != server_version:
        return send_file("/data/latest.csv", as_attachment=True)

    return jsonify({"status": "ok"})

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=7000, debug=True)
