# System-Analyzer-and-Expression-Plotting

## Descriere

**System Analyzer and Expression Plotting** este o aplicație web realizată în C++ și Python (Flask), având ca scop reprezentarea grafică a semnalelor în timp real și analiza sistemelor de control. Proiectul a fost dezvoltat utilizând principiile Programării Orientate pe Obiecte (OOP) și procesarea matematică a datelor.

Aplicația permite evaluarea expresiilor matematice în funcție de timp și analiza stabilității funcțiilor de transfer.



## Funcționalități

* Introducerea și evaluarea expresiilor matematice
* Generarea graficului unui semnal (pe baza pasului și a duratei[s])
* Analiza funcțiilor de transfer (numărător/numitor)
* Afișarea stabilității sistemului
* Calcularea și afișarea polilor și zerourilor



## Structura proiectului

Proiectul este alcătuit din următoarele module și fișiere principale:

* **ExpressionPlot** – evaluează expresiile matematice și generează punctele pentru grafic
* **SystemAnalyzer** – analizează funcția de transfer, calculând stabilitatea, polii și zerourile
* **tinyexpr** – parser C++ pentru evaluarea expresiilor matematice
* **app.py** – serverul Flask (API Backend) care face legătura între C++ și interfața web
* **index.html / script.js / style.css** – interfața utilizator și dezvoltarea graficului



## Tehnologii utilizate

* **C++** (POO, evaluare expresii, analiză matematică)
* **Python (Flask)** (Backend API)
* **JavaScript (Chart.js) / HTML / CSS** (Frontend & Reprezentare grafică)
* **Git & GitHub**



## Modul de funcționare

La pornirea aplicației, utilizatorul poate introduce o expresie matematică pentru a-i vizualiza graficul în timp real sau poate introduce coeficienții unei funcții de transfer pentru a analiza stabilitatea, polii și zerourile sistemului. Datele sunt procesate rapid în C++ și trimise prin Flask către interfața web unde sunt afișate interactiv cu Chart.js.



## Posibile îmbunătățiri/adăugări

* **Diagrama Bode** – Afișarea graficelor de amplitudine și de fază
* **Margini de stabilitate** – Calcularea marginii de fază și a marginii de câștig
* **Transformata Laplace** – Conversia unei funcții din domeniul timp în domeniul Laplace



## Autor

* **Rusu Andra-Ștefana**
