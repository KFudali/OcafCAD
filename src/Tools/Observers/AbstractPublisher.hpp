template <typename ObserverType>
class AbstractPublisher {
public:
    void addObserver(std::weak_ptr<ObserverType> obs) {
        mObservers.push_back(obs);
    }

protected:
    template <typename >
    void notifyObservers(ObserverHandle&& func) {
        for (auto it = mObservers.begin(); it != mObservers.end();) {
            if (auto obs = it->lock()) {
                func(*obs);
                ++it;
            } else {
                it = mObservers.erase(it);
            }
        }
    }

private:
    std::vector<std::weak_ptr<ObserverT>> mObservers;
};
