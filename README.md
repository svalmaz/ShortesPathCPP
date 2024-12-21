# Shortest Path 
### Характеристики алгоритма:
- Поиск в глубину (DFS) то базовый алгоритм обхода графа, который используется для поиска всех путей от начальной вершины до конечной
- Brute-force в том смысле, что алгоритм не делает никаких предположений о структуре графа и просто исследует все возможные пути между двумя вершинами, используя DFS.



### Метод FindPathsDFS:

- Выполняет поиск в глубину (DFS) для нахождения всех путей от начальной вершины до конечной.
- При достижении конечной вершины добавляет текущий путь в список всех путей.
- Применяет рекурсивный вызов для всех соседей текущей вершины, которые ещё не были посещены.
```cpp
	void FindPathsDFS(int current, int end, array<bool>^ visited, List<int>^ currentPath, List<List<int>^>^ allPaths)
	{
		visited[current] = true;
		currentPath->Add(current);

		if (current == end)
		{
			// Добавляем копию пути в список всех путей
			allPaths->Add(gcnew List<int>(currentPath));
		}
		else
		{
			// Ищем соседей текущей вершины
			for each (Tuple<int, int, double> ^ edge in edgesData)
			{
				int neighbor = -1;
				if (edge->Item1 == current && !visited[edge->Item2])
				{
					neighbor = edge->Item2;
				}
				else if (edge->Item2 == current && !visited[edge->Item1])
				{
					neighbor = edge->Item1;
				}

				if (neighbor != -1)
				{
					FindPathsDFS(neighbor, end, visited, currentPath, allPaths);
				}
			}
		}

		// Убираем текущую вершину из пути и отмечаем как непосещенную
		currentPath->RemoveAt(currentPath->Count - 1);
		visited[current] = false;
	}
```


### Метод FilterUniquePaths:

- Проверяет каждый путь, чтобы исключить те, которые содержат одинаковые рёбра.
- Если путь уникален, добавляет его в список уникальных путей и отмечает рёбра как использованные.
```cpp
List<List<int>^>^ FilterUniquePaths(List<List<int>^>^ allPaths)
{
	List<List<int>^>^ uniquePaths = gcnew List<List<int>^>();
	List<Tuple<int, int>^>^ usedEdges = gcnew List<Tuple<int, int>^>();

	for each (List<int> ^ path in allPaths)
	{
		bool isUnique = true;

		// Проверяем каждое ребро пути
		for (int i = 0; i < path->Count - 1; i++)
		{
			int u = path[i];
			int v = path[i + 1];
			Tuple<int, int>^ edge = gcnew Tuple<int, int>(u, v);

			// Если ребро уже используется в том же направлении, путь не уникален
			for each (Tuple<int, int> ^ usedEdge in usedEdges)
			{
				if (usedEdge->Item1 == edge->Item1 && usedEdge->Item2 == edge->Item2)
				{
					isUnique = false;
					break;
				}
			}

			if (!isUnique)
				break;
		}

		// Если путь уникален, добавляем его и отмечаем рёбра как использованные
		if (isUnique)
		{
			uniquePaths->Add(path);
			for (int i = 0; i < path->Count - 1; i++)
			{
				int u = path[i];
				int v = path[i + 1];
				Tuple<int, int>^ edge = gcnew Tuple<int, int>(u, v);
				usedEdges->Add(edge);
			}
		}
	}

	return uniquePaths;
}
```

