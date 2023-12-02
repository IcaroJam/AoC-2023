const fs = require("node:fs");

fs.readFile("../input.txt", "ascii", (err, data) => {
	if (err)
		return console.error("Failed to read input file :(\n", err);

	let ret = 0;

	const getHighest = (line, regex) => {
		let highest = 0;
		const matches = line.match(regex);

		if (matches !== null)
			matches.forEach((entry) => {
				const temp = parseInt(entry);
				
				if (temp > highest)
					highest = temp;
			});
		return highest;
	};

	const lines = data.split("\n");
	lines.forEach((line, i) => {
		if (line.length < 7) // If line's empty don't count it.
			return;
		let r = g = b = 0;
		r = getHighest(line, / \d* red/g);
		g = getHighest(line, / \d* green/g);
		b = getHighest(line, / \d* blue/g);

		ret += r * g * b;
	});

	console.log("Total sum of IDs is:", ret);
});
