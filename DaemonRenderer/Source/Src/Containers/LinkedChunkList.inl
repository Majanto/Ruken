/*
 *  MIT License
 *
 *  Copyright (c) 2019-2020 Basile Combet, Philippe Yi
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

template <typename TType, DAEsize TChunkSize>
LinkedChunkList<TType, TChunkSize>::~LinkedChunkList()
{
    // Removing all the nodes from the head to the tail
    while (m_tail != nullptr)
        DeleteNode(*m_head);
}

#pragma region Getters

template <typename TType, DAEsize TChunkSize>
DAEsize LinkedChunkList<TType, TChunkSize>::GetSize() const noexcept
{
    return m_size;
}

template <typename TType, DAEsize TChunkSize>
typename LinkedChunkList<TType, TChunkSize>::Node* LinkedChunkList<TType, TChunkSize>::GetHead() const noexcept
{
    return m_head;
}

template <typename TType, DAEsize TChunkSize>
typename LinkedChunkList<TType, TChunkSize>::Node* LinkedChunkList<TType, TChunkSize>::GetTail() const noexcept
{
    return m_tail;
}

#pragma endregion 

#pragma region Methods

template <typename TType, DAEsize TChunkSize>
typename LinkedChunkList<TType, TChunkSize>::Node& LinkedChunkList<TType, TChunkSize>::CreateNode() noexcept
{
    Node* new_node = new Node();
    m_size++;

    // If the list is empty
    if (m_tail == nullptr)
    {
        m_head = new_node;
        m_tail = new_node;

        return *new_node;
    }

    // Otherwise if the list has at least one node, inserting it at the end
    m_tail  ->next_node = new_node;
    new_node->prev_node = m_tail;
    m_tail              = new_node;

    return *new_node;
}

template <typename TType, DAEsize TChunkSize>
DAEvoid LinkedChunkList<TType, TChunkSize>::DeleteNode(Node& in_node) noexcept
{
    // Updating the head
    if (m_head == &in_node)
        m_head = in_node.next_node;

    // Updating the tail
    if (m_tail == &in_node)
        m_tail = in_node.prev_node;

    // Updating the next pointer
    if (in_node.next_node != nullptr)
        in_node.next_node->prev_node = in_node.prev_node;

    // Updating the prev pointer
    if (in_node.prev_node != nullptr)
        in_node.prev_node->next_node = in_node.next_node;

    m_size--;

    delete &in_node;
}

template <typename TType, DAEsize TChunkSize>
template <typename TLambda>
DAEvoid LinkedChunkList<TType, TChunkSize>::Foreach(TLambda in_lambda) noexcept
{
    for (Node* current_node = m_head; current_node != nullptr; current_node = current_node->next_node)
        in_lambda(*current_node);
}

#pragma endregion 