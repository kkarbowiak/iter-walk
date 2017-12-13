/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef ITER_WALK_H
#define ITER_WALK_H


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

                            typename Iterator::reference operator*() const
                            {
                                return *m_current;
                            }

                            bool is_first() const
                            {
                                return (m_current == m_first);
                            }

                            bool is_last() const
                            {
                                auto next = m_current;
                                ++next;
                                return (next == m_last);
                            }

                            Size get_index() const
                            {
                                return m_index;
                            }

                        private:
                            Iterator m_first;
                            Iterator m_last;
                            Iterator m_current;
                            Size m_index;
                    };

                public:
                    walk_iterator(Iterator first, Iterator last)
                        : m_first(first)
                        , m_last(last)
                        , m_current(first)
                        , m_index(0)
                    {
                    }

                    bool operator!=(walk_iterator const & other) const
                    {
                        return (m_current != other.m_current);
                    }

                    walk_proxy operator*() const
                    {
                        return walk_proxy(m_first, m_last, m_current, m_index);
                    }

                    walk_iterator & operator++()
                    {
                        ++m_current;
                        ++m_index;

                        return *this;
                    }

                private:
                    Iterator m_first;
                    Iterator m_last;
                    Iterator m_current;
                    Size m_index;
            };

        public:
            walker(Iterator first, Iterator last)
                : m_first(first)
                , m_last(last)
            {
            }

            walk_iterator begin() const
            {
                return walk_iterator(m_first, m_last);
            }

            walk_iterator end() const
            {
                return walk_iterator(m_last, m_last);
            }

        private:
            Iterator m_first;
            Iterator m_last;
    };

    template<class Iterator, class Size>
    walker<Iterator, Size> walk(Iterator first, Iterator last, Size /* unused */)
    {
        return walker<Iterator, Size>(first, last);
    }

    template<class Container>
    auto walk(Container & container) -> decltype(walk(container.begin(), container.end(), container.size()))
    {
        return walk(container.begin(), container.end(), container.size());
    }
}

#endif /* ITER_WALK_H */
