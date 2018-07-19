#pragma once

namespace siri {

	class SIRI_Size
	{
	public:
		SIRI_Size();
		SIRI_Size(int w, int h);
		~SIRI_Size();

	private:
		int m_w;
		int m_h;

	public:
		int getW();
		int getH();
		void setW(int w);
		void setH(int h);
	};

}