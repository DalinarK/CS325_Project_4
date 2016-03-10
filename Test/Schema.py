function PerfectMatching()
  Input: odds (list of odd vertices), G (adjacency list)
  while !odds.empty do
    v <-- odds.popFront()
    length <-- ∞
    for u ∈ odds do
      if weight(u,v) < length then
        length <-- weight(u,v)
        closest <-- u
      end if
    end for
    G.addEdge(closest,u)
    odds.remove(closest)
  end while
end function