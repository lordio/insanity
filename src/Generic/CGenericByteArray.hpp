#ifndef INSANITY_IMPLEMENTATION_GENERIC_BYTE_ARRAY
#define INSANITY_IMPLEMENTATION_GENERIC_BYTE_ARRAY

#include <Constants.hpp>

#include <IByteArray.hpp>
#include <vector>

#include <Default.hpp>

namespace Insanity
{
	class CGenericByteArray final : public IByteArray, public Default::Object
	{
		//TODO: test this workaround on GCC and XCode
		std::vector<u8> _vec{ {} };
		u64 _offset{ 0 };
	public:
		CGenericByteArray();
		~CGenericByteArray();

		//=================================================
		//Interface: IByteArray
		//=================================================
		void Write(u8 val) override;
		void Write(u16 val) override;
		void Write(u32 val) override;
		void Write(u64 val) override;
		void Write(s8 val) override;
		void Write(s16 val) override;
		void Write(s32 val) override;
		void Write(s64 val) override;
		void Write(bool val) override;
		void Write(float val) override;
		void Write(double val) override;
		void Write(long double val) override;
		void Write(IByteArray const * val) override;
		void Write(u8 const * val, u64 length) override;

		void Read(u8 & val) override;
		void Read(u16 & val) override;
		void Read(u32 & val) override;
		void Read(u64 & val) override;
		void Read(s8 & val) override;
		void Read(s16 & val) override;
		void Read(s32 & val) override;
		void Read(s64 & val) override;
		void Read(bool & val) override;
		void Read(float & val) override;
		void Read(double & val) override;
		void Read(long double & val) override;
		void Read(u8 * val, u64 length) override;

		u8 const * Array() const override;
		u64 Size() const override;
		void Clip() override;
		void Clear() override;
	};
}

#endif
