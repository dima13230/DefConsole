local console = {}

ext = {exit=sys.exit}

console.preloaded_code = ""

function console.stringRemoveAt(str, pos)
	return string.sub(str, 1, pos - 1) .. string.sub(str, pos + 1, string.len(str))
end

function console.insertString(str1, str2, pos)
	return str1:sub(1,pos)..str2..str1:sub(pos+1)
end

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