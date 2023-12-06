const fs = require("node:fs");

function getLocation(seed, maps) {
	let tmp = seed;

	for (const key in maps) {
		for (let i = 0; i < maps[key].length; i++) {
			if (tmp >= maps[key][i].src && tmp < maps[key][i].src + maps[key][i].rng) {
				tmp = maps[key][i].dst + (tmp - maps[key][i].src);
				break;
			}
		}
	}
	return tmp;
}

fs.readFile("../input.txt", "ascii", (err, data) => {
	if (err)
		return console.error("Failed to read input file :(\n", err);

	const seeds = [];
	const maps = { // Each entry in the arrays will be an object with the values for each line in the map.
		soil: [],
		fert: [],
		watr: [],
		lite: [],
		temp: [],
		humy: [],
		lctn: [],
	};

	const lines = data.split("\n");
	// First line is always seeds. Push each number into the seeds arr in Int form:
	lines[0].substring(lines[0].indexOf(":") + 2).split(" ").forEach(numStr => {seeds.push(parseInt(numStr))});
	// From this point on the pattern repeats for all maps:
	let i = 3;
	for (const key in maps) {
		while (lines[i] !== "") {
			const entry = {};
			const nums = lines[i].split(" ");

			entry.dst = parseInt(nums[0]);
			entry.src = parseInt(nums[1]);
			entry.rng = parseInt(nums[2]);
			maps[key].push(entry);
			i++;
		}
		i += 2;
	}

	const locations = seeds.map(seed => getLocation(seed, maps));

	console.log("Seeds:", seeds); 
	console.log("Maps:", maps);
	console.log("Locations:", locations);

	console.log("\nLowest location is:", Math.min(...locations));
});
