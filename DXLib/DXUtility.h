#pragma once


namespace DX
{
	class Delete_Release
	{
	public:
		template<class T>
		void operator()(T* p)
		{
			p->Release();
		}
	};
}