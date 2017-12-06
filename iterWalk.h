/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef ITER_WALK_H
#define ITER_WALK_H


namespace iter
{
    template<class Container>
    class walker
    {
        public:
            class walk_iterator
            {
                public:
                    class walk_proxy
                    {
                        public:
                            walk_proxy(typename Container::iterator first, typename Container::iterator last, typename Container::iterator current, typename Container::size_type index)
                                : m_first(first)
                                , m_last(last)
                                , m_current(current)
                                , m_index(index)
                            {
                            }

                            typename Container::reference operator*() const
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

                            typename Container::size_type get_index() const
                            {
                                return m_index;
                            }

                        private:
                            typename Container::iterator m_first;
                            typename Container::iterator m_last;
                            typename Container::iterator m_current;
                            typename Container::size_type m_index;
                    };

                public:
                    walk_iterator(typename Container::iterator first, typename Container::iterator last)
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
                    typename Container::iterator m_first;
                    typename Container::iterator m_last;
                    typename Container::iterator m_current;
                    typename Container::size_type m_index;
            };

        public:
            explicit walker(Container & container)
                : m_container(container)
            {
            }

            walk_iterator begin() const
            {
                return walk_iterator(m_container.begin(), m_container.end());
            }

            walk_iterator end() const
            {
                return walk_iterator(m_container.end(), m_container.end());
            }

        private:
            Container & m_container;
    };

    template<class Container>
    walker<Container> walk(Container & container)
    {
        return walker<Container>(container);
    }
}

#endif /* ITER_WALK_H */
