const fs = require("node:fs");

// For a set maximum time T, the total distance D can be calculated as follows:
//
// D = t' * v (where v is the velocity in mm/ms and t' is the time left after holding the button)
//   |
// D = (T - t) * v (where t is the time the button has been held)
//
// Now, since the velocity depends directly on t: v = 1 * t, which means:
// D = -t² + t * T
//
// In order to get the t values corresponding to the given record d, we need only resolve for:
// -t² + t * T - d = 0
// And round up for the lowest solution and down for the highest one to get the range of the times that result in a new record.
//
// And so:
// x1 = (-b + sqrt(b² -4ac)) / 2a
// x2 = (-b - sqrt(b² -4ac)) / 2a

// t = (-T +- sqrt(T² -4(-1)(-d))) / 2(-1)
function getWays(T, D) {
	const t1 = (-T + Math.sqrt(T * T - 4 * D)) / -2;
	const t2 = (-T - Math.sqrt(T * T - 4 * D)) / -2;

	return Math.ceil(t2 - 1) - Math.floor(t1 + 1) + 1;
}

fs.readFile("../input.txt", "ascii", (err, data) => {
	if (err)
		return console.error("Failed to read input file :(\n", err);

	const raceTable = {
		times: [],
		distances: []
	};
	let time;
	let dist;

	const lines = data.split("\n");
	raceTable.times = lines[0].match(/\d+/g);
	raceTable.distances = lines[1].match(/\d+/g);

	time = raceTable.times.join("");
	dist = raceTable.distances.join("");

	console.log("The race can be beat in this many ways:", getWays(time, dist));
});
