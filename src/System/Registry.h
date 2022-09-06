#pragma once

class Registry {

	public:

		static const uint NAME_WATCH_FACE = 0;
		static const uint NAME_APP = 1;
		static const uint NAME_SETTINGS = 2;

		static Registry *getInstance();

		uint getValue(uint address);

		void setValue(uint address, uint value);

	protected:

		static Registry *inst;

		Registry();
};
