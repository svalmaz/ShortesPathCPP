#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

#pragma once

namespace GraphApp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		TextBox^ weightl1;
		TextBox^ weightl2;
		TextBox^ vertex1Box;
		TextBox^ vertex2Box;
		TextBox^ weightBox;
		TextBox^ resultBox;
		Button^ drawMatrixEdgesButton;
		Button^ drawCustomEdgeButton;
		Button^ dijkstraButton;
		Button^ AllPathsButton;
		ListBox^ edgesListBox;
		array<Point>^ vertices;
		DataGridView^ matrixGridView;
		MenuStrip^ menuStrip;
		ToolStripMenuItem^ helpMenuItem;
		ToolStripMenuItem^ developerMenuItem;
		ToolStripMenuItem^ exitMenuItem;

		Point selectedVertex1;
		Point selectedVertex2;
		bool isVertex1Selected;
		TextBox^ weightInputBox;

		ComboBox^ comboBox;

		Label^ label1;
		Label^ label2;
		Label^ label3;

		bool graphExist = false;

		int selVert1;
		int selVert2;

		List<Tuple<int, int, double>^>^ edgesData;
		List<Tuple<int, int, double>^>^ nullData;
		array<array<double>^>^ adjacencyMatrix;

		void InitializeComponent(void)
		{
			this->weightl1 = (gcnew TextBox());
			this->weightl2 = (gcnew TextBox());
			this->resultBox = (gcnew TextBox());
			this->comboBox = (gcnew ComboBox());
			this->label2 = (gcnew Label());
			this->label1 = (gcnew Label());
			this->label3 = (gcnew Label());
			this->dijkstraButton = (gcnew Button());
			this->AllPathsButton = (gcnew Button());
			this->edgesListBox = (gcnew ListBox());
			this->edgesData = gcnew List<Tuple<int, int, double>^>();
			this->matrixGridView = (gcnew DataGridView());
			this->menuStrip = (gcnew MenuStrip());
			this->helpMenuItem = (gcnew ToolStripMenuItem(L"������"));
			this->developerMenuItem = (gcnew ToolStripMenuItem(L"� ���������"));
			this->exitMenuItem = (gcnew ToolStripMenuItem(L"�����"));
			this->SuspendLayout();

			//this->Font = gcnew System::Drawing::Font("Arial", 9, FontStyle::Regular);

			this->Icon = gcnew System::Drawing::Icon(L"icon.ico");

			this->BackColor = System::Drawing::Color::FromArgb(175, 132, 88);

			this->menuStrip->Items->AddRange(gcnew cli::array<ToolStripItem^>{
				this->helpMenuItem, this->developerMenuItem, this->exitMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1200, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip";
			this->Controls->Add(this->menuStrip);

			this->helpMenuItem->Click += gcnew EventHandler(this, &MainForm::helpMenuItem_Click);
			this->developerMenuItem->Click += gcnew EventHandler(this, &MainForm::developerMenuItem_Click);
			this->exitMenuItem->Click += gcnew EventHandler(this, &MainForm::exitMenuItem_Click);

			this->label1->Location = System::Drawing::Point(20, 80);
			this->label1->Name = L"label1";
			this->label1->Text = L"��������� �������:";
			this->label1->ForeColor = Color::White;
			this->label1->Size = System::Drawing::Size(120, 20);

			this->label2->Location = System::Drawing::Point(170, 80);
			this->label2->Name = L"label2";
			this->label2->Text = L"�������� �������:";
			this->label2->ForeColor = Color::White;
			this->label2->Size = System::Drawing::Size(120, 20);

			this->label3->Location = System::Drawing::Point(20, 30);
			this->label3->Name = L"label3";
			this->label3->Text = L"���������� ������:";
			this->label3->ForeColor = Color::White;
			this->label3->Size = System::Drawing::Size(140, 20);

			this->comboBox->Location = System::Drawing::Point(170, 30);
			this->comboBox->Size = System::Drawing::Size(120, 30);

			for (int i = 2; i <= 30; i++) {
				this->comboBox->Items->Add(i.ToString());
			}

			this->comboBox->SelectedIndex = 0;
			this->comboBox->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::drawButton_Click);

			this->weightl1->Location = System::Drawing::Point(20, 100);
			this->weightl1->Name = L"weightl1";
			this->weightl1->Size = System::Drawing::Size(120, 20);

			this->weightl2->Location = System::Drawing::Point(170, 100);
			this->weightl2->Name = L"weightl2";
			this->weightl2->Size = System::Drawing::Size(120, 20);

			this->matrixGridView = gcnew DataGridView();
			this->matrixGridView->Location = System::Drawing::Point(20, 450);
			this->matrixGridView->Size = System::Drawing::Size(400, 200);
			this->matrixGridView->AllowUserToAddRows = false;
			this->matrixGridView->AllowUserToDeleteRows = false;
			this->matrixGridView->ColumnHeadersVisible = true;
			this->matrixGridView->RowHeadersWidth = 50;
			this->matrixGridView->RowHeadersVisible = true;
			this->matrixGridView->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &MainForm::matrixGridView_CellEndEdit);
			this->Controls->Add(this->matrixGridView);

			this->dijkstraButton->Location = System::Drawing::Point(20, 720);
			this->dijkstraButton->Name = L"dijkstraButton";
			this->dijkstraButton->Size = System::Drawing::Size(200, 30);
			this->dijkstraButton->TabIndex = 3;
			this->dijkstraButton->Text = L"����� ���������� ����";
			this->dijkstraButton->UseVisualStyleBackColor = true;
			this->dijkstraButton->Click += gcnew EventHandler(this, &MainForm::DijkstraAlg);

			this->AllPathsButton->Location = System::Drawing::Point(20, 750);
			this->AllPathsButton->Name = L"AllPathsButton";
			this->AllPathsButton->Size = System::Drawing::Size(200, 30);
			this->AllPathsButton->TabIndex = 4;
			this->AllPathsButton->Text = L"����� ��� ��������� ����";
			this->AllPathsButton->UseVisualStyleBackColor = true;
			this->AllPathsButton->Click += gcnew EventHandler(this, &MainForm::FindAllPaths);
			this->Controls->Add(this->AllPathsButton);

			this->resultBox->Location = System::Drawing::Point(250, 720);
			this->resultBox->Name = L"resultBox";
			this->resultBox->Size = System::Drawing::Size(250, 30);

			this->edgesListBox->Location = System::Drawing::Point(1650, 50);
			this->edgesListBox->Name = L"edgesListBox";
			this->edgesListBox->Size = System::Drawing::Size(250, 100);
			this->edgesListBox->TabIndex = 5;

			this->MouseClick += gcnew MouseEventHandler(this, &MainForm::Form_MouseClick);

			this->weightInputBox = gcnew TextBox();
			this->weightInputBox->Visible = false;
			this->weightInputBox->KeyDown += gcnew KeyEventHandler(this, &MainForm::weightInputBox_KeyDown);
			this->weightInputBox->Size = System::Drawing::Size(50, 20);

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->edgesListBox);
			this->Controls->Add(this->dijkstraButton);
			this->Controls->Add(this->weightl1);
			this->Controls->Add(this->weightl2);
			this->Controls->Add(this->comboBox);
			this->Controls->Add(this->resultBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->matrixGridView);
			this->Controls->Add(this->weightInputBox);
			this->Name = L"MainForm";
			this->Text = L"���������� ����������� ����";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void weightInputBox_KeyDown(System::Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Enter)
			{
				double weight;

				if (Double::TryParse(weightInputBox->Text, weight))
				{
					if (Convert::ToInt32(weightInputBox->Text) <= 0) {

						MessageBox::Show("���� ������������� ����� ��������!", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
						this->matrixGridView->Rows[selVert1]->Cells[selVert2]->Value = "";
						return;

					}
					weightInputBox->Visible = false;

					if (selectedVertex1 == selectedVertex2) {
						MessageBox::Show(L"��������� � �������� ������� ������ ���� �������", L"������", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
					else {

						DrawEdge(selectedVertex1, selectedVertex2, weight);

						isVertex1Selected = false;

						double weight;

						Double::TryParse(weightInputBox->Text, weight);

						edgesData->Add(gcnew Tuple<int, int, double>(selVert1, selVert2, weight));
						edgesData->Add(gcnew Tuple<int, int, double>(selVert2, selVert1, weight));

						edgesListBox->Items->Add(String::Format("�����: {0} -> {1}, ���: {2}", selVert1, selVert2, weight));
						edgesListBox->Items->Add(String::Format("�����: {0} -> {1}, ���: {2}", selVert2, selVert1, weight));

						matrixGridView->Rows[selVert1]->Cells[selVert2]->Value = weightInputBox->Text;
						matrixGridView->Rows[selVert2]->Cells[selVert1]->Value = weightInputBox->Text;

						Graphics^ g = this->CreateGraphics();
						Pen^ redPen = gcnew Pen(Color::FromArgb(175, 132, 88), 3);
						g->DrawEllipse(redPen, selectedVertex1.X - 15 - 3, selectedVertex1.Y - 15 - 3, (15 + 3) * 2, (15 + 3) * 2);


						bool edgeExists = false;
						for (int i = 0; i < edgesData->Count; i++)
						{
							if (edgesData[i]->Item1 == selVert1 && edgesData[i]->Item2 == selVert2)
							{
								edgesData[i] = gcnew Tuple<int, int, double>(selVert1, selVert2, weight);
								edgeExists = true;
								break;
							}
						}

						g->Clear(Color::FromArgb(175, 132, 88));

						paintGraph();

						weightInputBox->Text = "";

					}

				}
				else
				{
					MessageBox::Show(L"������� ���������� ���!", L"������", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		bool IsPointInCircle(Point point, Point center, int radius)
		{
			double distance = Math::Sqrt(Math::Pow(point.X - center.X, 2) + Math::Pow(point.Y - center.Y, 2));
			return distance <= radius;
		}

		void Form_MouseClick(System::Object^ sender, MouseEventArgs^ e)
		{

			if (graphExist) {

				for (int i = 0; i < vertices->Length; i++)
				{
					if (IsPointInCircle(e->Location, vertices[i], 15))
					{
						if (!isVertex1Selected)
						{
							selVert1 = i;
							selectedVertex1 = vertices[i];
							isVertex1Selected = true;

							Graphics^ g = this->CreateGraphics();
							Pen^ bluePen = gcnew Pen(Color::Blue, 3);
							g->DrawEllipse(bluePen, selectedVertex1.X - 15 - 3, selectedVertex1.Y - 15 - 3, (15 + 3) * 2, (15 + 3) * 2);

						}
						else
						{
							selVert2 = i;
							selectedVertex2 = vertices[i];

							weightInputBox->Location = Point(e->Location.X + 20, e->Location.Y + 20);
							weightInputBox->Visible = true;
							weightInputBox->Focus();
						}
						return;
					}
					else if (i + 1 == vertices->Length) {
						Graphics^ g = this->CreateGraphics();
						Pen^ redPen = gcnew Pen(Color::FromArgb(175, 132, 88), 3);
						g->DrawEllipse(redPen, selectedVertex1.X - 15 - 3, selectedVertex1.Y - 15 - 3, (15 + 3) * 2, (15 + 3) * 2);
						isVertex1Selected = false;
					}
				}
			}
		}

	private:
		void helpMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
		{
			MessageBox::Show(L"��� ����������� ��������� ��� ������ � ���������� ��������.", L"������", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void developerMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
		{
			MessageBox::Show(L"���������: ���������� ��������� ���������� ����������� ���������� ����� ����� ��������� � �����\n������: 1.3\n���: 2024\n�����������: ������� ���������", L"� ���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void exitMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
		{
			Application::Exit();
		}

	private:
		void DijkstraAlg(System::Object^ sender, System::EventArgs^ e)
		{
			resultBox->Text = "";
			if (weightl1->Text->Length > 0 && weightl2->Text->Length > 0)
			{
				int start = Convert::ToInt32(weightl1->Text);
				int end = Convert::ToInt32(weightl2->Text);

				List<int>^ path;
				int n = vertices->Length;

				// ������������� ��� ��������� ��������
				array<double>^ distance = gcnew array<double>(n);
				array<int>^ parent = gcnew array<int>(n);
				array<bool>^ visited = gcnew array<bool>(n);

				for (int i = 0; i < n; i++)
				{
					distance[i] = Double::PositiveInfinity;
					parent[i] = -1;
					visited[i] = false;
				}

				distance[start] = 0;

				
				SortedDictionary<double, int>^ priorityQueue = gcnew SortedDictionary<double, int>(); // ������
				priorityQueue->Add(0, start);

				while (priorityQueue->Count > 0)
				{
					double minDistance;
					int current;

					// �������� ������ ������� � ������� enumerator
					auto enumerator = priorityQueue->GetEnumerator();
					if (enumerator.MoveNext())
					{
						// ��������� ���� � ��������
						minDistance = enumerator.Current.Key;
						current = enumerator.Current.Value;
					}
					else
					{
						break; // ����� �� ����� ���� ������ ��� ���������
					}

					// �������� �������� � ����������� �����������
					priorityQueue->Remove(minDistance);

					// ��������, ��� �� ���� �������
					if (visited[current])
						continue;

					visited[current] = true;

					// ��������� ���������� � ������� �������� ����
					for each (Tuple<int, int, double> ^ edge in edgesData)
					{
						// �������� � ���� ������������ - �� current � ������� � ��������
						if (edge->Item1 == current) // ����������� current -> neighbor
						{
							int neighbor = edge->Item2;
							double weight = edge->Item3;


							if (!visited[neighbor] && distance[current] + weight < distance[neighbor])
							{
								distance[neighbor] = distance[current] + weight;
								parent[neighbor] = current;

								// ��������� ������� � ������� � �����������
								if (!priorityQueue->ContainsKey(distance[neighbor])) {
									priorityQueue->Add(distance[neighbor], neighbor);
								}
								else {
									// ��������� ����������� �����
									double modifiedKey = distance[neighbor];
									while (priorityQueue->ContainsKey(modifiedKey)) {
										modifiedKey += 0.0001; // ��������� ��������� �����
									}
									priorityQueue->Add(modifiedKey, neighbor);
								}

							}
						}

						// �������� �����������: neighbor -> current
						if (edge->Item2 == current) // ����������� neighbor -> current
						{
							int neighbor = edge->Item1;
							double weight = edge->Item3;

							if (!visited[neighbor] && distance[current] + weight < distance[neighbor])
							{
								distance[neighbor] = distance[current] + weight;
								parent[neighbor] = current;

								// ��������� ������� � ������� � �����������
								if (!priorityQueue->ContainsKey(distance[neighbor])) {
									priorityQueue->Add(distance[neighbor], neighbor);
								}
								else {
									// ��������� ����������� �����
									double modifiedKey = distance[neighbor];
									while (priorityQueue->ContainsKey(modifiedKey)) {
										modifiedKey += 0.0001; // ��������� ��������� �����
									}
									priorityQueue->Add(modifiedKey, neighbor);
								}

							}
						}
					}
				}





				// ��������� ����������
				if (distance[end] == Double::PositiveInfinity)
				{
					path = nullptr;
					MessageBox::Show(L"����� ������ ������� ����� ����");
				}
				else
				{
					path = gcnew List<int>();
					for (int v = end; v != -1; v = parent[v])
					{
						path->Insert(0, v);
					}

					paintGraph();

					for (int i = 0; i < path->Count; i++)
					{
						resultBox->Text += path[i].ToString();
						if (i + 1 != path->Count)
						{
							resultBox->Text += "->";
						}

						if (i + 2 <= path->Count)
						{
							int resultWeight = 0;

							for each (Tuple<int, int, double> ^ edge in edgesData)
							{
								if ((edge->Item1 == path[i] && edge->Item2 == path[i + 1]) ||
									(edge->Item2 == path[i] && edge->Item1 == path[i + 1]))
								{
									resultWeight = edge->Item3;
								}
							}
							DrawBlueEdge(vertices[path[i]], vertices[path[i + 1]], resultWeight);
						}
					}

					MessageBox::Show(String::Format("���� �� ��������� ������� �� �������� ������� = {2}", weightl1->Text, weightl2->Text, Convert::ToString(distance[end])));
				}
			}
			else
			{
				MessageBox::Show(L"������� ���������� �����");
			}
		}


		void drawButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			int n;
			if (Int32::TryParse(comboBox->SelectedItem->ToString(), n) && n > 0)
			{
				matrixGridView->ColumnCount = n;

				for (int i = 0; i < n; i++) {
					matrixGridView->Columns[i]->Name = i.ToString();
					matrixGridView->Columns[i]->Width = 30;
				}
				matrixGridView->RowCount = n;
				for (int i = 0; i < n; i++) {
					matrixGridView->Rows[i]->HeaderCell->Value = i.ToString();
				}
				this->DrawGraph(n);
				graphExist = true;
			}
			else
			{
				MessageBox::Show(L"������� ���������� �����");
			}
		}

		void drawCustomEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			int vertex1, vertex2;
			double weight;

			if (Int32::TryParse(vertex1Box->Text, vertex1) && Int32::TryParse(vertex2Box->Text, vertex2) && Double::TryParse(weightBox->Text, weight))
			{
				if (vertex1 >= 0 && vertex1 < vertices->Length && vertex2 >= 0 && vertex2 < vertices->Length)
				{
					adjacencyMatrix[vertex1][vertex2] = weight;
					this->DrawEdge(vertices[vertex1], vertices[vertex2], weight);

					edgesData->Add(gcnew Tuple<int, int, double>(vertex1, vertex2, weight));

					edgesListBox->Items->Add(String::Format("�����: {0} <-> {1}, ���: {2}", vertex1, vertex2, weight));
				}
				else
				{
					MessageBox::Show(L"������� �������������� �������");
				}
			}
			else
			{
				MessageBox::Show(L"������� ���������� �����");
			}
		}

		void DrawGraph(int n)
		{
			Graphics^ g = this->CreateGraphics();
			g->Clear(Color::FromArgb(175, 132, 88));

			weightl1->Text = "";
			weightl2->Text = "";

			edgesListBox->Items->Clear();

			int radius = 200;
			int centerX = this->ClientSize.Width / 2;
			int centerY = this->ClientSize.Height / 2;
			float angleStep = 360.0f / n;

			vertices = gcnew array<Point>(n);
			adjacencyMatrix = gcnew array<array<double>^>(n);
			for (int i = 0; i < n; i++)
			{
				matrixGridView->Rows[i]->Cells[i]->ReadOnly = true;
				adjacencyMatrix[i] = gcnew array<double>(n);
				for (int j = 0; j < n; j++)
				{
					adjacencyMatrix[i][j] = Double::PositiveInfinity;
				}
			}


			for (int i = 0; i < n; i++)
			{
				float angle = i * angleStep;
				int x = centerX + (int)(radius * Math::Cos(angle * Math::PI / 180.0));
				int y = centerY + (int)(radius * Math::Sin(angle * Math::PI / 180.0));

				vertices[i] = Point(x, y);

				g->DrawEllipse(Pens::Black, x - 15, y - 15, 30, 30);
				g->DrawString(i.ToString(), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::Black, x - 10, y - 10);
			}
			this->matrixGridView->ColumnCount = n;
			this->matrixGridView->RowCount = n;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					this->matrixGridView->Rows[i]->Cells[j]->Value = "";
				}
			}
			for (int i = 0; i < n; i++)
			{
				matrixGridView->Rows[i]->Cells[i]->Value = "0";
				matrixGridView->Rows[i]->Cells[i]->ReadOnly = true;
				matrixGridView->Rows[i]->Cells[i]->Style->BackColor = Color::FromArgb(75, 0, 130);
			}

		}

		void matrixGridView_CellEndEdit(System::Object^ sender, DataGridViewCellEventArgs^ e)
		{
			int row = e->RowIndex;
			int col = e->ColumnIndex;

			double weight;
			String^ cellValue = this->matrixGridView->Rows[row]->Cells[col]->Value->ToString();

			if (Double::TryParse(cellValue, weight))
			{
				if (weight <= 0) {
					MessageBox::Show("���� ������������� ����� ��������!", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
					this->matrixGridView->Rows[row]->Cells[col]->Value = "";
					return;
				}

				// ����������� �������� � ������� ��������� �����������
				adjacencyMatrix[row][col] = weight;
				adjacencyMatrix[col][row] = weight;

				UpdateEdge(row, col, weight);
				UpdateEdge(col, row, weight);

				paintGraph();

				// ������ ��� ����������� ����
				this->DrawEdge(vertices[row], vertices[col], weight);
				this->DrawEdge(vertices[col], vertices[row], weight);
			}
			else
			{
				// ������������� �������� � ������� ��� ������������� ��� ����� �����������
				adjacencyMatrix[row][col] = Double::PositiveInfinity;
				adjacencyMatrix[col][row] = Double::PositiveInfinity;

				// ������� ���� ��� ����� �����������
				RemoveEdge(row, col);
				RemoveEdge(col, row);

				Graphics^ g = this->CreateGraphics();
				g->Clear(Color::White);
				this->DrawGraph(vertices->Length);

				for each(auto edge in edgesData)
				{
					this->DrawEdge(vertices[edge->Item1], vertices[edge->Item2], edge->Item3);
				}
			}
		}

		void paintGraph() {

			DrawGraph(vertices->Length);

			edgesListBox->Items->Clear();

			for (int i = 0; i < edgesData->Count; i++)
			{
				for (int j = i + 1; j < edgesData->Count; j++)
				{
					if (edgesData[i]->Item1 == edgesData[j]->Item1 &&
						edgesData[i]->Item2 == edgesData[j]->Item2)
					{
						edgesData->RemoveAt(j);
						j--;
					}
				}
			}

			for each (Tuple<int, int, double> ^ edge in edgesData) {

				int first = edge->Item1;
				int second = edge->Item2;
				double weight = edge->Item3;

				Point vertc1;
				Point vertc2;

				for (int i = 0; i < vertices->Length; i++) {
					if (i == first) {
						vertc1 = vertices[i];
					}
					if (i == second) {
						vertc2 = vertices[i];
					}
				}
				DrawEdge(vertc1, vertc2, weight);

				matrixGridView->Rows[first]->Cells[second]->Value = weight;

				edgesListBox->Items->Add(String::Format("�����: {0} <-> {1}, ���: {2}", first, second, weight));
			}
		}

		void DrawEdge(Point p1, Point p2, double weight)
		{

			if (p1 == p2) {
				MessageBox::Show(L"��������� � �������� ������� ������ ���� �������", L"������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {

				Graphics^ g = this->CreateGraphics();
				Pen^ edgePen = gcnew Pen(Color::Black, 3);

				const int radius = 15;

				double deltaX = p2.X - p1.X;
				double deltaY = p2.Y - p1.Y;
				double angle = atan2(deltaY, deltaX);

				Point p1Edge = Point(
					p1.X + radius * cos(angle),
					p1.Y + radius * sin(angle)
				);

				Point p2Edge = Point(
					p2.X - radius * cos(angle),
					p2.Y - radius * sin(angle)
				);

				g->DrawLine(edgePen, p1Edge, p2Edge);



				SizeF textSize = g->MeasureString(weight.ToString(), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular));

				PointF middlePoint = PointF(((p1Edge.X + p2Edge.X) / 2) - ((weight.ToString()->Length) * 4), ((p1Edge.Y + p2Edge.Y) / 2) - 6);

				//RectangleF textBackground = RectangleF(middlePoint.X - 2, middlePoint.Y - 2, textSize.Width + 4, textSize.Height + 4);

				//g->FillRectangle(gcnew SolidBrush(Color::FromArgb(175, 132, 88)), textBackground);

				g->DrawString(weight.ToString(), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::White, middlePoint);
			}
		}

		void DrawBlueEdge(Point p1, Point p2, double weight)
		{

			if (p1 == p2) {
				MessageBox::Show(L"��������� � �������� ������� ������ ���� �������", L"������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {

				Graphics^ g = this->CreateGraphics();
				Pen^ edgePen = gcnew Pen(Color::Blue, 3);

				const int radius = 15;

				double deltaX = p2.X - p1.X;
				double deltaY = p2.Y - p1.Y;
				double angle = atan2(deltaY, deltaX);

				Point p1Edge = Point(
					p1.X + radius * cos(angle),
					p1.Y + radius * sin(angle)
				);

				Point p2Edge = Point(
					p2.X - radius * cos(angle),
					p2.Y - radius * sin(angle)
				);

				g->DrawLine(edgePen, p1Edge, p2Edge);

				this->DrawBlueArrow(g, p1Edge, p2Edge);

				SizeF textSize = g->MeasureString(weight.ToString(), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular));

				PointF middlePoint = PointF(((p1Edge.X + p2Edge.X) / 2) - ((weight.ToString()->Length) * 4), ((p1Edge.Y + p2Edge.Y) / 2) - 6);

				//RectangleF textBackground = RectangleF(middlePoint.X - 2, middlePoint.Y - 2, textSize.Width + 4, textSize.Height + 4);

				//g->FillRectangle(gcnew SolidBrush(Color::FromArgb(175, 132, 88)), textBackground);

				g->DrawString(weight.ToString(), gcnew System::Drawing::Font("Arial", 10, FontStyle::Regular), Brushes::White, middlePoint);
			}
		}

		// ��������������� ����������� ������� ������ ���� �������� �� ������� ������ AllPaths
		void FindAllPaths(System::Object^ sender, System::EventArgs^ e)
		{
			resultBox->Text = "";

			if (weightl1->Text->Length > 0 && weightl2->Text->Length > 0)
			{
				int start = Convert::ToInt32(weightl1->Text);
				int end = Convert::ToInt32(weightl2->Text);

				// ������������� ��� �������� �����
				List<List<int>^>^ allPaths = gcnew List<List<int>^>();
				List<int>^ currentPath = gcnew List<int>();
				array<bool>^ visited = gcnew array<bool>(vertices->Length);

				// ����� ������������ ������ ��� ������ �����
				FindPathsDFS(start, end, visited, currentPath, allPaths);

				// ���������� ���������� ����� ��� ����������� �� �����
				List<List<int>^>^ uniquePaths = FilterUniquePaths(allPaths);

				// ����� ���� ���������� ����� � resultBox
				if (uniquePaths->Count == 0)
				{
					MessageBox::Show(L"��� ����� ����� ����� ���������.");
				}
				else
				{
					for each (List<int> ^ path in uniquePaths)
					{
						for (int i = 0; i < path->Count; i++)
						{
							resultBox->Text += path[i].ToString();
							if (i + 1 != path->Count)
							{
								resultBox->Text += "->";
							}
						}
						resultBox->Text += "\r\n";
					}
				}
			}
			else
			{
				MessageBox::Show(L"������� ���������� �����");
			}
		}

		void FindPathsDFS(int current, int end, array<bool>^ visited, List<int>^ currentPath, List<List<int>^>^ allPaths)
		{
			visited[current] = true;
			currentPath->Add(current);

			if (current == end)
			{
				// ��������� ����� ���� � ������ ���� �����
				allPaths->Add(gcnew List<int>(currentPath));
			}
			else
			{
				// ���� ������� ������� �������
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

			// ������� ������� ������� �� ���� � �������� ��� ������������
			currentPath->RemoveAt(currentPath->Count - 1);
			visited[current] = false;
		}

		List<List<int>^>^ FilterUniquePaths(List<List<int>^>^ allPaths)
		{
			List<List<int>^>^ uniquePaths = gcnew List<List<int>^>();
			List<Tuple<int, int>^>^ usedEdges = gcnew List<Tuple<int, int>^>();

			for each (List<int> ^ path in allPaths)
			{
				bool isUnique = true;

				// ��������� ������ ����� ����
				for (int i = 0; i < path->Count - 1; i++)
				{
					int u = path[i];
					int v = path[i + 1];
					Tuple<int, int>^ edge = gcnew Tuple<int, int>(u, v);

					// ���� ����� ��� ������������ � ��� �� �����������, ���� �� ��������
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

				// ���� ���� ��������, ��������� ��� � �������� ���� ��� ��������������
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
		//void AllPaths(System::Object^ sender, System::EventArgs^ e)
		//{
		//	// ��������� ��������� � �������� �������
		//	int start = Convert::ToInt32(weightl1->Text);
		//	int end = Convert::ToInt32(weightl2->Text);

		//	// �������� �� ������������ �����
		//	if (start < 0 || end < 0)
		//	{
		//		MessageBox::Show(L"������� ���������� ��������� � �������� �������.");
		//		return;
		//	}

		//	// ���� ������ ���� ������� ����� � ��������
		//	List<List<int>^>^ adjacencyList = gcnew List<List<int>^>();

		//	// ���������� ��� ������ ���� �����
		//	List<List<int>^>^ allPaths = gcnew List<List<int>^>();
		//	Stack<int>^ path = gcnew Stack<int>();
		//	array<bool>^ visited = gcnew array<bool>(adjacencyList->Count);

		//	// ������������� ������� ���������
		//	for (int i = 0; i < adjacencyList->Count; ++i)
		//	{
		//		visited[i] = false;
		//	}

		//	// ��������� ����� ���� �����
		//	FindAllPaths(start, end, adjacencyList, visited, path, allPaths);

		//	// ������������ �������������� ������
		//	String^ resultMessage = L"��� ��������� ���� ����� ���������:\n";
		//	for each(List<int> ^ singlePath in allPaths)
		//	{
		//		for each(int vertex in singlePath)
		//		{
		//			resultMessage += Convert::ToString(vertex) + L" ";
		//		}
		//		resultMessage += L"\n";
		//	}

		//	// ����������� ����������
		//	MessageBox::Show(resultMessage);
		//}


		

		void UpdateEdge(int row, int col, double weight)
		{
			bool edgeExists = false;

			// ���������, ���� �� ��� ����� � ������
			for (int i = 0; i < edgesData->Count; i++)
			{
				if (edgesData[i]->Item1 == row && edgesData[i]->Item2 == col)
				{
					// ��������� ��� ������������� �����
					edgesData[i] = gcnew Tuple<int, int, double>(row, col, weight);
					edgesListBox->Items[i] = String::Format("�����: {0} <-> {1}, ���: {2}", row, col, weight);
					edgeExists = true;
					break;
				}
			}

			// ���� ����� �� �������, ��������� �����
			if (!edgeExists)
			{
				edgesData->Add(gcnew Tuple<int, int, double>(row, col, weight));
				edgesListBox->Items->Add(String::Format("�����: {0} <-> {1}, ���: {2}", row, col, weight));
			}
		}

		void RemoveEdge(int row, int col)
		{
			for (int i = 0; i < edgesData->Count; i++)
			{
				if (edgesData[i]->Item1 == row && edgesData[i]->Item2 == col)
				{
					// ������� ����� �� ������ ����
					edgesData->RemoveAt(i);
					edgesListBox->Items->RemoveAt(i);
					break;
				}
			}
		}

		void DrawArrow(Graphics^ g, Point p1, Point p2)
		{
			float arrowSize = 10.0f;
			float angle = Math::Atan2(p2.Y - p1.Y, p2.X - p1.X);

			PointF arrowEnd = PointF(p2.X, p2.Y);
			PointF arrowLeft = PointF(p2.X - arrowSize * Math::Cos(angle - Math::PI / 6), p2.Y - arrowSize * Math::Sin(angle - Math::PI / 6));
			PointF arrowRight = PointF(p2.X - arrowSize * Math::Cos(angle + Math::PI / 6), p2.Y - arrowSize * Math::Sin(angle + Math::PI / 6));

			g->DrawLine(Pens::Black, arrowEnd, arrowLeft);
			g->DrawLine(Pens::Black, arrowEnd, arrowRight);
		}

		void DrawBlueArrow(Graphics^ g, Point p1, Point p2)
		{
			float arrowSize = 10.0f;
			float angle = Math::Atan2(p2.Y - p1.Y, p2.X - p1.X);

			PointF arrowEnd = PointF(p2.X, p2.Y);
			PointF arrowLeft = PointF(p2.X - arrowSize * Math::Cos(angle - Math::PI / 6), p2.Y - arrowSize * Math::Sin(angle - Math::PI / 6));
			PointF arrowRight = PointF(p2.X - arrowSize * Math::Cos(angle + Math::PI / 6), p2.Y - arrowSize * Math::Sin(angle + Math::PI / 6));

			g->DrawLine(Pens::Blue, arrowEnd, arrowLeft);
			g->DrawLine(Pens::Blue, arrowEnd, arrowRight);
		}
	};
}
