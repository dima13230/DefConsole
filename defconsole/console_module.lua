local console = {}

console.preloaded_code = ""



function console.evalString(str)
	local status, result = pcall(loadstring, "return "..str)
	if status then
		if result == nil then
			return "Syntax or other error in the code"
		else
			return result()
		end
	else
		return result
	end
end

return console