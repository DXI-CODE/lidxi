from flask import Flask, request, send_file, jsonify

app = Flask(__name__)

# Define tu versión del servidor
SERVER_VERSION = "1.0.0"

@app.route('/get-version', methods=['POST'])
def get_version():
    client_data = request.get_json()
    if not client_data or "version" not in client_data:
        return jsonify({"error": "Missing 'version' in request body"}), 400

    client_version = client_data["version"]

    if client_version == SERVER_VERSION:
        return jsonify({"status": "ok"}), 200
    else:
        # Envía el archivo CSV si no coincide
        return send_file('/data/latest.csv', as_attachment=True)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=7000)
