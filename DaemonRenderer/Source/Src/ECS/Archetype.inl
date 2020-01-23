/*
 *  MIT License
 *
 *  Copyright (c) 2019 Basile Combet, Philippe Yi
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

template <typename ... TComponents>
template <typename ... TItems, DAEsize ... TIds>
EntityID Archetype<TComponents...>::CreateEntityHelper(TItems&&... in_entity_items, std::index_sequence<TIds...>) noexcept
{
    std::tuple<TItems&&...> items { std::forward<TItems>(in_entity_items)... };

	(std::get<TIds>(m_components).CreateItem(std::forward<TItems>(std::get<TIds>(items))), ...);
    return EntityID {EntitiesCount() - 1};
}

template <typename ... TComponents>
template <DAEsize... TIds>
EntityID Archetype<TComponents...>::CreateEntityHelper(std::index_sequence<TIds...>) noexcept
{
	(std::get<TIds>(m_components).CreateItem(), ...);
    return EntityID {EntitiesCount() - 1};
}

template <typename ... TComponents>
template <DAEsize... TIds>
DAEvoid Archetype<TComponents...>::SetupFingerprint(std::index_sequence<TIds...>) noexcept
{
    (m_fingerprint.AddTrait(std::get<TIds>(m_components).TypeId()), ...);
}

template <typename ... TComponents>
Archetype<TComponents...>::Archetype()
{
    SetupFingerprint(std::make_index_sequence<sizeof...(TComponents)>());
}

template <typename ... TComponents>
template <typename TComponent>
auto Archetype<TComponents...>::GetComponent() noexcept
{
    return std::reference_wrapper(std::get<TComponent>(m_components));
}

template <typename ... TComponents>
template <DAEsize TIndex>
auto Archetype<TComponents...>::GetComponent() noexcept
{
    return std::reference_wrapper(std::get<TIndex>(m_components));
}

template <typename ... TComponents>
template <typename ... TItems>
EntityID Archetype<TComponents...>::CreateEntity(TItems&&... in_entity_items) noexcept
{
    return CreateEntityHelper<TItems...>(std::forward<TItems>(in_entity_items)..., std::make_index_sequence<sizeof...(TComponents)>());
}

template <typename ... TComponents>
EntityID Archetype<TComponents...>::CreateEntity() noexcept
{
    return CreateEntityHelper(std::make_index_sequence<sizeof...(TComponents)>());
}

template <typename ... TComponents>
DAEsize Archetype<TComponents...>::EntitiesCount() const noexcept
{
    return std::get<0>(m_components).GetItemCount();
}

template <typename ... TComponents>
ArchetypeFingerprint const& Archetype<TComponents...>::GetFingerprint() const noexcept
{
    return m_fingerprint;
}