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

fs.readFile("./test.txt", "ascii", (err, data) => {
	if (err)
		return console.error("Failed to read input file :(\n", err);

	let seedRanges = "";
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
	// The pattern repeats for all maps:
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

	// So apparently storing every seed just eats up all my memory, so lets process each one individualy and move on to the next (which will take 5-12 working years lol):
	let lowestLocation;
	seedRanges = lines[0].substring(lines[0].indexOf(":") + 2).split(" ");
	console.log(seedRanges);
	for (let i = 0; i < seedRanges.length; i += 2) {
		const base = parseInt(seedRanges[i]);
		const range = parseInt(seedRanges[i + 1]);

		for (let j = 0; j < range; j++) {
			const tmploc = getLocation(base + j, maps);

			if (lowestLocation === undefined || tmploc < lowestLocation)
				lowestLocation = tmploc;
		}
	}

	console.log("\nLowest location is:", lowestLocation);
});
