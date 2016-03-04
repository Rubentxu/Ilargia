#ifndef MATCHER
#define MATCHER

#include <stdexcept>
#include <memory>

namespace Entitas {

    class Entity;

    class IAnyOfMatcher;

    class INoneOfMatcher;

    class IAllOfMatcher;

    class IMatcher {
    public:
        virtual const std::vector<int> &Getindices() const = 0;
        virtual bool Matches(const std::shared_ptr<Entity> &entity) = 0;
    };

    class Matcher : public IAllOfMatcher, public IAnyOfMatcher, public INoneOfMatcher {
        std::vector<int> _indices;
        std::vector<int> _allOfIndices;
        std::vector<int> _anyOfIndices;
        std::vector<int> _noneOfIndices;
        int _hash = 0;
        bool _isHashCached = false;
        std::string _toStringCache;

        Matcher();

        std::vector<int> mergeIndices();

        //static void appendIndices(const std::shared_ptr<StringBuilder> &sb, const std::string &prefix, std::vector<int> &indexArray, std::vector<std::string> &componentNames);

        static bool equalIndices(std::vector<int> &i1, std::vector<int> &i2);

        static int applyHash(int hash, std::vector<int> &indices, int i1, int i2);

        static std::vector<int> mergeIndices(std::vector<IMatcher> &matchers);

        static std::vector<std::string> getComponentNames(std::vector<IMatcher> &matchers);

        static void setComponentNames(const std::shared_ptr<Matcher> &matcher, std::vector<IMatcher> &matchers);

        //static std::vector<int> distinctIndices(const std::shared_ptr<IEnumerable<int> > &indices);

    public:
        const std::vector<int> &Getindices() const;

        const std::vector<int> &GetallOfIndices() const;

        const std::vector<int> &GetanyOfIndices() const;

        const std::vector<int> &GetnoneOfIndices() const;

        std::shared_ptr<IAnyOfMatcher> IAllOfMatcher_AnyOf(std::vector<int> &indices);

        std::shared_ptr<IAnyOfMatcher> IAllOfMatcher_AnyOf(std::vector<IMatcher> &matchers);

        std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<int> &indices);

        std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<IMatcher> &matchers);

        bool Matches(const std::shared_ptr<Entity> &entity);

        virtual bool Equals(const std::shared_ptr<void> &obj);

        virtual int GetHashCode();

        static std::shared_ptr<IAllOfMatcher> AllOf(std::vector<int> &indices);

        static std::shared_ptr<IAllOfMatcher> AllOf(std::vector<IMatcher> &matchers);

        static std::shared_ptr<IAnyOfMatcher> AnyOf(std::vector<int> &indices);

        static std::shared_ptr<IAnyOfMatcher> AnyOf(std::vector<IMatcher> &matchers);

        std::vector<std::string> componentNames;

        virtual std::string ToString();

    };

    class MatcherException : public std::exception {
    public:
        MatcherException(const std::shared_ptr<IMatcher> &matcher);

    protected:
        std::shared_ptr<MatcherException> shared_from_this() {
            return std::static_pointer_cast<MatcherException>(shared_from_this());
        }
    };

    class IMatcherExtension final : public std::enable_shared_from_this<IMatcherExtension> {
    public:
        static std::shared_ptr<TriggerOnEvent> OnEntityAdded(const std::shared_ptr<IMatcher> &matcher);

        static std::shared_ptr<TriggerOnEvent> OnEntityRemoved(const std::shared_ptr<IMatcher> &matcher);

        static std::shared_ptr<TriggerOnEvent> OnEntityAddedOrRemoved(const std::shared_ptr<IMatcher> &matcher);
    };

    class ICompoundMatcher : public IMatcher {
    public:
        virtual const std::vector<int> &GetallOfIndices() const = 0;
        virtual const std::vector<int> &GetanyOfIndices() const = 0;
        virtual const std::vector<int> &GetnoneOfIndices() const = 0;
    };

    class IAllOfMatcher : public ICompoundMatcher {
    public:
        virtual std::shared_ptr<IAnyOfMatcher> AnyOf(std::vector<int> &indices) = 0;
        virtual std::shared_ptr<IAnyOfMatcher> AnyOf(std::vector<IMatcher> &matchers) = 0;
        virtual std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<int> &indices) = 0;
        virtual std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<IMatcher> &matchers) = 0;
    };

    class IAnyOfMatcher : public ICompoundMatcher {
    public:
        virtual std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<int> &indices) = 0;
        virtual std::shared_ptr<INoneOfMatcher> NoneOf(std::vector<IMatcher> &matchers) = 0;
    };

    class INoneOfMatcher : public ICompoundMatcher {
    };
}


#endif	//#ifndef MATCHER
