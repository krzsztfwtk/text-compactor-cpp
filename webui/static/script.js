document.getElementById('configForm').addEventListener('submit', function(e) {
    e.preventDefault();

    const formData = {
        input: document.getElementById('textInput').value,
        wordlist: document.getElementById('wordlist').value,
        capitalNamesBoost: parseFloat(document.getElementById('capitalNamesBoost').value),
        stopWordsList: document.getElementById('stopWordsList').value,
        selectivityRatio: parseFloat(document.getElementById('selectivityRatio').value),
        tags: parseInt(document.getElementById('tags').value, 10),
        measure: document.getElementById('measure').value,
        query: document.getElementById('queryInput') ? document.getElementById('queryInput').value : '',
        queryBoostFactor: document.getElementById('queryBoostFactor') ? parseFloat(document.getElementById('queryBoostFactor').value) : 0,
    };

    fetch('/compact_text', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(formData),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`Network response was not ok (${response.status})`);
        }
        return response.json().catch(() => {
            throw new Error('The response was not JSON.');
        });
    })
    
    .then(data => {
        const preElement = document.querySelector('#result pre');
        if (data.error) {
            preElement.textContent = 'Error: ' + data.error;
        } else {
            preElement.textContent = data.output;
        }
    })
    
    .catch(error => {
        console.error('Error:', error);
        document.getElementById('result').textContent = error.toString();
    });
});
