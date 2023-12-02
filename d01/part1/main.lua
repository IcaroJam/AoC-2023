FilePath = "../input.txt"

local inFile = io.open(FilePath, "r")
if not inFile then
	error("Failed to open the input file :(")
	return nil
end

local calVals = {}
for line in io.lines(FilePath) do
	local nums = {}
	for num in line:gmatch("%d") do
		table.insert(nums, tonumber(num))
	end -- Fill a table with all the numeric matches.
	if #nums > 0 then
		table.insert(calVals, nums[1] * 10 + nums[#nums]) -- Get the first and last matches from the aforementioned table and insert the corresponding calibration value into a table.
	end
end

local finalSum = 0
for i, val in ipairs(calVals) do
	finalSum = finalSum + val
end

print("The sum of al calibration values is:", finalSum)
