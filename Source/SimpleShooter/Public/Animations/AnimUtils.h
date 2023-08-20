#pragma once

class AnimUtils
{
public:
	template<typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animations)
	{
		if (!Animations) return nullptr;
		const auto NotifieEvents = Animations->Notifies;

		for (auto NotifieEvent : NotifieEvents)
		{
			auto AnimNotify =  Cast<T>(NotifieEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}
};
