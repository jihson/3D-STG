#pragma once


namespace HyEngine
{

	class Object /*: public IObject*/
	{

	public:
		explicit Object();
	public:
		virtual ~Object();

	protected:

		virtual void Initialize() = 0;
	public:
		// ----------------------------------
		// PUBLIC METHODS
		// -----------------------------------
		inline UINT GetInstanceID() { return m_id; }
		inline 	bool CompareName(std::wstring name) { return m_name == name; }
		std::wstring ToString() { return m_name; }

		// -----------------------------------
		// STATIC METHODS
		// -----------------------------------
		static void Destroy(Object* obj)
		{
			obj->m_bWantsDestroy = true;
		}
		// ------------------------------------
		// OPERATORS
		// -----------------------------------
		inline bool operator != (Object* other) { return this->GetInstanceID() != other->GetInstanceID(); }
		inline bool operator == (Object* other) { return this->GetInstanceID() == other->GetInstanceID(); }


	private:
		std::wstring m_name;
		LONGLONG m_id;


	public:
		bool m_bWantsDestroy;


	};
}