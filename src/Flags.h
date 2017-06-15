#pragma once

class Flags {
public: 
	bool test = false;
	bool fresnel = false;
	bool bvh = false;
	bool bvhtest = false;
	bool gi = false;
	bool gitest = false;
	bool csgtest = false;
	bool transform = true;
	unsigned int mode = 1; // BLINNPHONG MODE
	unsigned int ss = 1; // DEFAULT
};