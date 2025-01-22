#include <iostream>
#include <memory>
#include <fstream>
#include <list>
#include <stdexcept>

template <typename T>
class IObserver {
public:
	virtual ~IObserver() = default;
	virtual void OnEvent(const T& event_data) = 0;
};

template <typename T>
class Subject {
public:
	Subject();
	~Subject();

	void Attach(std::shared_ptr<IObserver<T>> observer);
	void Detach(std::shared_ptr<IObserver<T>> observer);
	void Notify(const T& event_data);

private:
	class SubjectImpl;
	std::unique_ptr<SubjectImpl> impl_;
};

template <typename T>
class Subject<T>::SubjectImpl {
public:
	void Attach(std::shared_ptr<IObserver<T>> observer) {
		list_observer_.push_back(observer);
	}

	void Detach(std::shared_ptr<IObserver<T>> observer) {
		list_observer_.remove(observer);
	}

	void Notify(const T& event_data) {
		for (auto& observer : list_observer_) {
			if (observer) {
				observer->OnEvent(event_data);
			}
		}
	}

private:
	std::list<std::shared_ptr<IObserver<T>>> list_observer_;
};

template <typename T>
Subject<T>::Subject() : impl_(std::make_unique<SubjectImpl>()) {}

template <typename T>
Subject<T>::~Subject() = default;

template <typename T>
void Subject<T>::Attach(std::shared_ptr<IObserver<T>> observer) {
	impl_->Attach(observer);
}

template <typename T>
void Subject<T>::Detach(std::shared_ptr<IObserver<T>> observer) {
	impl_->Detach(observer);
}

template <typename T>
void Subject<T>::Notify(const T& event_data) {
	impl_->Notify(event_data);
}

template <typename T>
class ConsoleObserver : public IObserver<T> {
public:
	void OnEvent(const T& event_data) override {
		std::cout << event_data << std::endl;
	}
};

template <typename T>
class LoggingObserver : public IObserver<T> {
public:
	LoggingObserver(std::ofstream& output_file) : output_file_(output_file) {}

	void OnEvent(const T& event_data) override {
		output_file_ << event_data << std::endl;
	}

private:
	std::ofstream& output_file_;
};

class CustomEvent {
public:
	std::string id;
	std::string type;
	std::string payload;
};

std::ostream& operator<<(std::ostream& out, const CustomEvent& event) {
	out << "id: " << event.id << ", type: " << event.type << ", payload: " << event.payload;
	return out;
}

int main() {
	std::ofstream out("out.txt");
	if (!out.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	Subject<int> int_subject;

	auto int_console_observer = std::make_shared<ConsoleObserver<int>>();
	auto int_logging_observer = std::make_shared<LoggingObserver<int>>(out);
	int_subject.Attach(int_console_observer);
	int_subject.Attach(int_logging_observer);
	int_subject.Notify(999);

	Subject<std::string> string_subject;

	auto string_console_observer = std::make_shared<ConsoleObserver<std::string>>();
	auto string_logging_observer = std::make_shared<LoggingObserver<std::string>>(out);
	string_subject.Attach(string_console_observer);
	string_subject.Attach(string_logging_observer);
	string_subject.Notify("hello!");

	Subject<CustomEvent> custom_subject;
	auto custom_console_observer = std::make_shared<ConsoleObserver<CustomEvent>>();
	auto custom_logging_observer = std::make_shared<LoggingObserver<CustomEvent>>(out);
	custom_subject.Attach(custom_console_observer);
	custom_subject.Attach(custom_logging_observer);
	CustomEvent event{"999", "data", "payload data"};
	custom_subject.Notify(event);

	return 0;
}