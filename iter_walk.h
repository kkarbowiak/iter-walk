/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef ITER_WALK_H
#define ITER_WALK_H

#include <iterator>


namespace iter
{
    template<class Iterator, class Size>
    class walker
    {
        public:
            class walk_iterator
            {
                public:
                    class walk_proxy
                    {
                        public:
                            walk_proxy(Iterator first, Iterator last, Iterator current, Size index)
                                : m_first(first)
                                , m_last(last)
                                , m_current(current)
                                , m_index(index)
                            {
                            }

                            auto operator*() const -> typename Iterator::reference
                            {
                                return get();
                            }

                            auto is_first() const -> bool
                            {
                                return (m_current == m_first);
                            }

                            auto is_last() const -> bool
                            {
                                return (std::next(m_current) == m_last);
                            }

                            auto get() const -> typename Iterator::reference
                            {
                                return *m_current;
                            }

                            auto get_index() const -> Size
                            {
                                return m_index;
                            }

                            auto get_iterator() const -> Iterator
                            {
                                return m_current;
                            }

                        private:
                            Iterator const m_first;
                            Iterator const m_last;
                            Iterator const m_current;
                            Size const m_index;
                    };

                public:
                    walk_iterator(Iterator first, Iterator last)
                        : m_first(first)
                        , m_last(last)
                        , m_current(first)
                        , m_index(0)
                    {
                    }

                    auto operator!=(walk_iterator const & other) const -> bool
                    {
                        return (m_current != other.m_current);
                    }

                    auto operator*() const -> walk_proxy
                    {
                        return walk_proxy(m_first, m_last, m_current, m_index);
                    }

                    auto operator++() -> walk_iterator &
                    {
                        ++m_current;
                        ++m_index;

                        return *this;
                    }

                private:
                    Iterator const m_first;
                    Iterator const m_last;
                    Iterator m_current;
                    Size m_index;
            };

        public:
            walker(Iterator first, Iterator last)
                : m_first(first)
                , m_last(last)
            {
            }

            auto begin() const -> walk_iterator
            {
                return walk_iterator(m_first, m_last);
            }

            auto end() const -> walk_iterator
            {
                return walk_iterator(m_last, m_last);
            }

        private:
            Iterator const m_first;
            Iterator const m_last;
    };

    template<class Iterator, class Size>
    inline auto walk(Iterator first, Iterator last, Size /* unused */) -> walker<Iterator, Size>
    {
        return walker<Iterator, Size>(first, last);
    }

    template<class Container>
    inline auto walk(Container & container) -> decltype(walk(std::begin(container), std::end(container), container.size()))
    {
        return walk(std::begin(container), std::end(container), container.size());
    }

    template<class Container>
    inline auto rwalk(Container & container) -> decltype(walk(container.rbegin(), container.rend(), container.size()))
    {
        return walk(container.rbegin(), container.rend(), container.size());
    }
}

#endif /* ITER_WALK_H */
