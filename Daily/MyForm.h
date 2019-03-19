#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
//#include <iostream>
#include <fstream> 
//#include <iomanip> 
#include <iterator>
#include <msclr\marshal_cppstd.h>
#include <algorithm>
namespace Daily 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace std;
	using namespace msclr::interop;
	time_t t = time(0);
	struct tm * now = localtime(&t); //время
	bool isEmpty = 0; //пустой ли
	bool isAll = 0; //вывод всех или только даты
	int index = -1; //индекс отсчета 0 - всё, не 0 - вывод с определенного значения
	int index_to_delete = -1; //индекс элемента для удаления
	vector<std::string> data; //вектор данных
	char check_date[80]; 
	string check_date_str; //контроль выбранной даты
	string check_date_str_add; //контроль даты в части создания нового элемента
	string h_add; 
	string m_add;
	string d_add; //час, минута, данные добавляемого элемента
	void split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	} // классы разделения строки через разделитель
	std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			cur_date->Text = String::Format("Сегодня {0}.{1}.{2}", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
			strftime(check_date, 80, "%d.%m.%Y", now);
			check_date_str = string(check_date);
			check_date_str_add = check_date_str;
			setlocale(LC_ALL, "rus");
			ifstream fout("data.txt");
			if (!fout.is_open()) // если файл небыл открыт
			{
				cur_date->Text += "\n\nФайл не найден/не открывается, создан пустой проект!"; // напечатать соответствующее сообщение
				isEmpty = 1;
			}
			else
			{
				std::string str;
				do
				{
					getline(fout, str);
					if (str != "")
					{
						data.insert(data.end(), str);
					}
				} while (fout);
			}
			if (data.size() == 0)
				isEmpty = 1;
			output(isAll);
			label1->Text = "";
					
		}
		void output(bool x)
		{
			label1->Text = "";
			output_box->Items->Clear();
			index_to_delete = -1;
			if (isEmpty == 1)
			{
				output_box->Items->Add("Нет данных!");
				return;
			}
			index = -1;
			
			if (x)
			{
				index = 0;
				for (int i = 0; i < data.size(); i++)
				{
					vector<string> step = split(data[i], '\\');
					string s = "";
					s = step[0] + " " + step[1] + " " + step[2];
					output_box->Items->Add(gcnew System::String(s.c_str()));
				}
			}
			else
			{
				for (int i = 0; i < data.size(); i++)
				{
					vector<string> step = split(data[i], '\\');
					string s = "";
					s = step[1] + " " + step[2];
					if (step[0] == check_date_str)
					{
						if (index == -1)
							index = i;
						output_box->Items->Add(gcnew System::String(s.c_str()));
					}

				}
			}
		}


















	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DateTimePicker^  Time_Picker_Main;
	protected:

	private: System::Windows::Forms::Label^  cur_date;
	private: System::Windows::Forms::Button^  show_all;
	private: System::Windows::Forms::Button^  clear_data;
	private: System::Windows::Forms::Button^  save_button;
	private: System::Windows::Forms::ListBox^  output_box;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;
	private: System::Windows::Forms::ComboBox^  hour_combobox;
	private: System::Windows::Forms::ComboBox^  minute_combobox;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  add_button;
	private: System::Windows::Forms::Button^  delete_button;
private: System::Windows::Forms::Label^  label1;

	protected:
	private:
		System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Time_Picker_Main = (gcnew System::Windows::Forms::DateTimePicker());
			this->cur_date = (gcnew System::Windows::Forms::Label());
			this->show_all = (gcnew System::Windows::Forms::Button());
			this->clear_data = (gcnew System::Windows::Forms::Button());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->output_box = (gcnew System::Windows::Forms::ListBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->hour_combobox = (gcnew System::Windows::Forms::ComboBox());
			this->minute_combobox = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->add_button = (gcnew System::Windows::Forms::Button());
			this->delete_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Time_Picker_Main
			// 
			this->Time_Picker_Main->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->Time_Picker_Main->Location = System::Drawing::Point(27, 24);
			this->Time_Picker_Main->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Time_Picker_Main->Name = L"Time_Picker_Main";
			this->Time_Picker_Main->Size = System::Drawing::Size(132, 22);
			this->Time_Picker_Main->TabIndex = 0;
			this->Time_Picker_Main->ValueChanged += gcnew System::EventHandler(this, &MyForm::Time_Picker_Main_ValueChanged);
			// 
			// cur_date
			// 
			this->cur_date->AutoSize = true;
			this->cur_date->Location = System::Drawing::Point(27, 61);
			this->cur_date->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->cur_date->Name = L"cur_date";
			this->cur_date->Size = System::Drawing::Size(46, 17);
			this->cur_date->TabIndex = 1;
			this->cur_date->Text = L"label1";
			// 
			// show_all
			// 
			this->show_all->Location = System::Drawing::Point(686, 138);
			this->show_all->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->show_all->Name = L"show_all";
			this->show_all->Size = System::Drawing::Size(133, 52);
			this->show_all->TabIndex = 2;
			this->show_all->Text = L"Вывести все записи";
			this->show_all->UseVisualStyleBackColor = true;
			this->show_all->Click += gcnew System::EventHandler(this, &MyForm::show_all_Click);
			// 
			// clear_data
			// 
			this->clear_data->Location = System::Drawing::Point(686, 78);
			this->clear_data->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->clear_data->Name = L"clear_data";
			this->clear_data->Size = System::Drawing::Size(133, 52);
			this->clear_data->TabIndex = 3;
			this->clear_data->Text = L"Очистить данные";
			this->clear_data->UseVisualStyleBackColor = true;
			this->clear_data->Click += gcnew System::EventHandler(this, &MyForm::clear_data_Click);
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(686, 18);
			this->save_button->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(133, 52);
			this->save_button->TabIndex = 4;
			this->save_button->Text = L"Сохранение";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &MyForm::save_button_Click);
			// 
			// output_box
			// 
			this->output_box->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->output_box->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->output_box->FormattingEnabled = true;
			this->output_box->HorizontalScrollbar = true;
			this->output_box->ItemHeight = 20;
			this->output_box->Location = System::Drawing::Point(27, 198);
			this->output_box->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->output_box->Name = L"output_box";
			this->output_box->Size = System::Drawing::Size(800, 184);
			this->output_box->TabIndex = 5;
			this->output_box->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::output_box_SelectedIndexChanged);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker1->Location = System::Drawing::Point(292, 24);
			this->dateTimePicker1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(120, 22);
			this->dateTimePicker1->TabIndex = 6;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &MyForm::dateTimePicker1_ValueChanged);
			// 
			// hour_combobox
			// 
			this->hour_combobox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->hour_combobox->FormattingEnabled = true;
			this->hour_combobox->Items->AddRange(gcnew cli::array< System::Object^  >(24) {
				L"00", L"01", L"02", L"03", L"04", L"05", L"06",
					L"07", L"08", L"09", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23"
			});
			this->hour_combobox->Location = System::Drawing::Point(420, 24);
			this->hour_combobox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->hour_combobox->Name = L"hour_combobox";
			this->hour_combobox->Size = System::Drawing::Size(52, 24);
			this->hour_combobox->TabIndex = 7;
			// 
			// minute_combobox
			// 
			this->minute_combobox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->minute_combobox->FormattingEnabled = true;
			this->minute_combobox->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"00", L"05", L"10", L"15", L"20", L"25",
					L"30", L"35", L"40", L"45", L"50", L"55"
			});
			this->minute_combobox->Location = System::Drawing::Point(480, 24);
			this->minute_combobox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->minute_combobox->Name = L"minute_combobox";
			this->minute_combobox->Size = System::Drawing::Size(52, 24);
			this->minute_combobox->TabIndex = 8;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(293, 61);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(239, 22);
			this->textBox1->TabIndex = 9;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// add_button
			// 
			this->add_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_button->Location = System::Drawing::Point(27, 138);
			this->add_button->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->add_button->Name = L"add_button";
			this->add_button->Size = System::Drawing::Size(240, 52);
			this->add_button->TabIndex = 10;
			this->add_button->Text = L"Добавить заметку";
			this->add_button->UseVisualStyleBackColor = true;
			this->add_button->Click += gcnew System::EventHandler(this, &MyForm::add_button_Click);
			// 
			// delete_button
			// 
			this->delete_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->delete_button->Location = System::Drawing::Point(292, 138);
			this->delete_button->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->delete_button->Name = L"delete_button";
			this->delete_button->Size = System::Drawing::Size(240, 52);
			this->delete_button->TabIndex = 11;
			this->delete_button->Text = L"Удалить заметку";
			this->delete_button->UseVisualStyleBackColor = true;
			this->delete_button->Click += gcnew System::EventHandler(this, &MyForm::delete_button_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(547, 209);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 17);
			this->label1->TabIndex = 12;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(832, 395);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->delete_button);
			this->Controls->Add(this->add_button);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->minute_combobox);
			this->Controls->Add(this->hour_combobox);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->output_box);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->clear_data);
			this->Controls->Add(this->show_all);
			this->Controls->Add(this->cur_date);
			this->Controls->Add(this->Time_Picker_Main);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MinimumSize = System::Drawing::Size(842, 418);
			this->Name = L"MyForm";
			this->Text = L"Ежедневник";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion 

	private: System::Void show_all_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		isAll = 1;
		output(isAll);
	}

			 private: System::Void Time_Picker_Main_ValueChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 label1->Text = "";
				 check_date_str = marshal_as<std::string>(Time_Picker_Main->Text);
				 isAll = 0;
				 output(isAll);
			 }

	private: System::Void clear_data_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		isEmpty = 1;
		data.clear();
		output(isAll);
	}
	private: System::Void save_button_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		index_to_delete = -1;
		ofstream out;
		out.open("data.txt");
		for (int i = 0; i < data.size(); i++)
		{
			out << data[i] << endl;
		}
		out.close();
	}
	private: System::Void output_box_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		index_to_delete = output_box->SelectedIndex;
	}

	private: System::Void delete_button_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		if (index_to_delete == -1)
		{
			label1->Text = "Ошибка! Не выбран объект удаления!";
			return;
		}
		if (isAll)
		{
			output_box->Items->Clear();
			data.erase(data.begin() + index_to_delete);
			index_to_delete = -1;
			if (data.size() == 0)
				isEmpty = 1;
			output(isAll);
		}
		if (!isAll)
		{
			output_box->Items->Clear();
			data.erase(data.begin() + index + index_to_delete);
			index_to_delete = -1;
			if (data.size() == 0)
				isEmpty = 1;
			output(isAll);
		}
	}
	private: System::Void add_button_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		if (textBox1->Text == "")
		{
			label1->Text = "Ошибка! Нет введенного описания!";
			return;
		}
		isEmpty = 0;
		string check;
		h_add = marshal_as<std::string>(hour_combobox->Text);
		m_add = marshal_as<std::string>(minute_combobox->Text);
		if (h_add == "")
			h_add = "00";
		if (m_add == "")
			m_add = "00";
		check = check_date_str_add + "\\" + h_add + ":" + m_add + "\\" + marshal_as<std::string>(textBox1->Text);
		data.push_back(check);
		sort(data.begin(), data.end());
		output(isAll);
	}
	private: System::Void dateTimePicker1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		label1->Text = "";
		check_date_str_add = marshal_as<std::string>(dateTimePicker1->Text);
	}

private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
