FilePath = "../input.txt"

local inFile = io.open(FilePath, "r")
if not inFile then
	error("Failed to open the input file :(")
	return nil
end

NumDict = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
}

local calVals = {}
for line in io.lines(FilePath) do
	local nums = {}
	-- Fill a table with the numeric and alphanumeric matches and their corresponding index in the line.
	local i = line:find("%d")
	while i ~= nil do
		table.insert(nums, {i, tonumber(string.sub(line, i, i))})
		i = line:find("%d", i + 1)
	end
	for j, entry in ipairs(NumDict) do
		i = line:find(entry)
		while i ~= nil do
			table.insert(nums, {i, j}) -- The Dict index of each number equals it's value.
			i = line:find(entry, i + 1)
		end
	end

	table.sort(nums, function(a, b)
		return a[1] < b[1]
	end) -- Sort the table in function of the index of each entry in the line.

	for j, num in ipairs(nums) do
		print(nums[j][1], nums[j][2])
	end

	if #nums > 0 then
		table.insert(calVals, nums[1][2] * 10 + nums[#nums][2]) -- Get the first and last matches from the aforementioned table and insert the corresponding calibration value into a table.
	end
end

local finalSum = 0
for i, val in ipairs(calVals) do
	finalSum = finalSum + val
end

print("The sum of al calibration values is:", finalSum)
