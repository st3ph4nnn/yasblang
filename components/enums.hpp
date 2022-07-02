#pragma once

enum operations {
	add = -99,
	substract = -98,
	multiply = -97,
	divide = -96,
	power = -95,
	modulo = -94
};

enum symbols {
	equal = -93,
	greater_than = -92,
	lower_than = -91
};

enum token_type {
    keyword = -1,

    other = 0,

    v_num = 1,
    v_str = 2,
    word = 3,
    end = 4
};
