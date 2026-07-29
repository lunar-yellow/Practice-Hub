from flask import Flask, render_template, request, jsonify
import subprocess
import json
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

# ruta pentru generare grafic
@app.route('/generate', methods=['POST'])
def generate():
    data = request.get_json()
    
    # calea catre executabil
    program = os.path.join(os.getcwd(), "program.exe")

    try:
        # inlocuire virgula cu punct pentru a nu avea erori intre conexiunea dintre py si cpp
        step = str(data.get('step', '0.01')).replace(',', '.').strip()
        duration = str(data.get('duration', '10')).replace(',', '.').strip()
        expression = str(data.get('expression', '')).strip()

        # apelare cpp pentru grafic
        rezultat = subprocess.run([program, step, duration, expression], capture_output=True, text=True)
        output = (rezultat.stdout or "").strip()

        if not output:
            return jsonify({'success': False, 'error': 'Programul C++ nu a returnat date!'})

        parsed_data = json.loads(output)

        # verificam daca cpp a dat eroare(eroare la pas sau durata)
        if isinstance(parsed_data, dict) and 'error' in parsed_data:
            return jsonify({'success': False, 'error': parsed_data['error']})

        return jsonify({'success': True, 'signal': parsed_data})

    except Exception as e:
        return jsonify({'success': False, 'error': str(e)})

# ruta pentru analiza functiei de transfer
@app.route('/analyze', methods=['POST'])
def analyze():
    data = request.get_json()
    
    # calea catre executabil
    program = os.path.join(os.getcwd(), "program.exe")

    try:
        numarator = str(data.get('numarator', '')).replace(',', '.').strip()
        numitor = str(data.get('numitor', '')).replace(',', '.').strip() 

        if not numarator or not numitor:
            return jsonify({'success': False, 'error': 'Introdu numărătorul și numitorul!'})

        # apelare cpp pentru functia de transfer
        rezultat = subprocess.run([program, numarator, numitor], capture_output=True, text=True)
        output = (rezultat.stdout or "").strip()

        if not output:
            return jsonify({'success': False, 'error': 'Programul C++ nu a returnat date!'})

        date_analiza = json.loads(output)

        # verificam daca cpp a dat eroare
        if isinstance(date_analiza, dict) and 'error' in date_analiza:
            return jsonify({'success': False, 'error': date_analiza['error']})

        return jsonify({'success': True, 'analysis': date_analiza})

    except Exception as e:
        return jsonify({'success': False, 'error': str(e)})

if __name__ == '__main__':
    app.run(debug=True)