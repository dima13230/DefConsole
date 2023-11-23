function evalString(str)
	return assert(loadstring("return "..str))()
end
