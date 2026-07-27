from flask import Flask, render_template, request, jsonify
import subprocess
import json
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/process', methods=['POST'])
def process():
    data = request.get_json()
    action = data.get('type')
    
    # calea catre executabil
    program = os.path.join(os.getcwd(), "program.exe")

    try:
        # pentru generare grafic
        if action == 'generate':
            step = str(data.get('step', 0.01))
            duration = str(data.get('duration', 10))
            expression = str(data.get('expression', ''))

            # apelare cpp pentru grafic
            rezultat = subprocess.run([program, step, duration, expression], capture_output=True, text=True)
            output = (rezultat.stdout or "").strip()

            if not output:
                return jsonify({'success': False, 'error': 'Programul C++ nu a returnat date!'})

            return jsonify({'success': True, 'signal': json.loads(output)})

        # pentru analiza functiei de transfer
        elif action == 'analyze':
            numarator = str(data.get('numarator', '')).strip()
            numitor = str(data.get('numitor', '')).strip() 

            if not numarator or not numitor:
                return jsonify({'success': False, 'error': 'Introdu numărătorul și numitorul!'})

            # apelare cpp pentru functia de transfer
            rezultat = subprocess.run([program, numarator, numitor], capture_output=True, text=True)
            output = (rezultat.stdout or "").strip()

            if not output:
                return jsonify({'success': False, 'error': 'Programul C++ nu a returnat date!'})

            date_analiza = json.loads(output)
            return jsonify({'success': True, 'analysis': date_analiza})

    except Exception as e:
        return jsonify({'success': False, 'error': str(e)})

if __name__ == '__main__':
    app.run(debug=True) #imi deschide serverul local pe web pentru testare