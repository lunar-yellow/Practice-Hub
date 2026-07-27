let chart = null;

// generare grafic!!

document.getElementById("generate").addEventListener("click", async () => {
    const expression = document.getElementById("expression").value;
    const step = parseFloat(document.getElementById("step").value);
    const duration = parseFloat(document.getElementById("duration").value);

    try {
        const response = await fetch("/process", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                type: "generate",
                expression: expression,
                step: step,
                duration: duration
            })
        });

        const data = await response.json();

        if (!data.success) {
            alert("Eroare backend: " + data.error);
            return;
        }

        const points = data.signal.map(p => ({
            x: p.time,
            y: p.value
        }));

        DrawChart(points);

    } catch (error) {
        console.error("Eroare JS/Fetch:", error);
        alert("Eroare comunicare backend");
    }
});

function DrawChart(points) {
    const ctx = document.getElementById("chart");

    if (chart) {
        chart.destroy();
    }

    const signalColor = "#c87aff";

    chart = new Chart(ctx, {
        type: "line",
        data: {
            datasets: [
                {//hover pentru cursor
                    label: "Semnal",
                    data: points,
                    parsing: true,
                    borderColor: signalColor,
                    backgroundColor: signalColor,
                    borderWidth: 2,
                    pointRadius: 0,
                    pointHoverRadius: 6,
                    pointHoverBackgroundColor: "#ffffff",
                    pointHoverBorderColor: signalColor,
                    tension: 0,
                    fill: false
                }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            interaction: {
                mode: "nearest",
                intersect: false
            },
            plugins: {
                legend: {
                    labels: { color: "white", font: { size: 15 } }
                },
                title: {
                    display: true,
                    text: "Semnal în timp",
                    color: "white",
                    font: { size: 22, weight: "bold" }
                },
                tooltip: {
                    enabled: true,
                    backgroundColor: "#222",
                    titleColor: signalColor,
                    bodyColor: "white",
                    displayColors: false,
                    callbacks: {
                        label: function(context) {
                            return [
                                "Timp = " + context.parsed.x.toFixed(3) + " s",
                                "Amplitudine = " + context.parsed.y.toFixed(4)
                            ];
                        }
                    }
                }
            },
            scales: {
                x: {
                    type: "linear",
                    min: 0,
                    grid: { color: "#606060", lineWidth: 1 },
                    ticks: {
                        color: "white",
                        maxTicksLimit: 10,
                        callback: function(value) { return Number(value).toFixed(1); },
                        font: { size: 13 }
                    },
                    title: {
                        display: true,
                        text: "Timp [s]",
                        color: "white",
                        font: { size: 16, weight: "bold" }
                    }
                },
                y: {
                    grid: { color: "#606060", lineWidth: 1 },
                    ticks: {
                        color: "white",
                        callback: function(value) { return Number(value).toFixed(1); },
                        font: { size: 13 }
                    },
                    title: {
                        display: true,
                        text: "Amplitudine",
                        color: "white",
                        font: { size: 16, weight: "bold" }
                    }
                }
            }
        }
    });
}

// analiza functie de transfer

document.getElementById('analyze').addEventListener('click', async () => {
    const numarator = document.getElementById('numarator').value;
    const numitor = document.getElementById('numitor').value;

    if (!numarator.trim() || !numitor.trim()) {
        alert("Introdu valori atât pentru numărător, cât și pentru numitor (ex: '1 2' și '1 3 2')");
        return;
    }

    try {
        const response = await fetch('/process', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 
                type: "analyze",
                numarator: numarator, 
                numitor: numitor 
            })
        });

        const data = await response.json();

        if (data.success) {
            const res = data.analysis;
            const rows = document.querySelectorAll('#resultsTable tr');
            
            if (rows.length >= 3) {
                rows[0].children[1].textContent = res.stabilitate;
                rows[1].children[1].textContent = res.poli;
                rows[2].children[1].textContent = res.zerouri;
            }
        } else {
            alert('Eroare backend: ' + data.error);
        }
    } catch (error) {
        console.error('Eroare JS/Fetch:', error);
        alert('Eroare la comunicarea cu serverul pentru analiză.');
    }
});