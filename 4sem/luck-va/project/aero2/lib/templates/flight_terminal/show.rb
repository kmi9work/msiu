"
<table class = 'list'>
" +
  if @user and !@user[:is_super]
  "
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
  </caption>
  "
  else
    ''
  end +
  "
  <tbody>
    <tr>
      <th>
        Название:
      </th>
      <th>
        #{@item.terminal[:name]}
      </th>  
    </tr>
    <tr>
      <th>
        Описание:
      </th>
      <th>  
        #{@item.terminal[:description]}
      </th>
    </tr>
    <tr>
      <th>
        Нужен ли автобус?:
      </th>
      <th>  
        #{@item.terminal[:needs_bus] ? "Да" : "Нет"}
      </th>
    </tr>
    <tr>
      <th>
        Информация:
      </th>
      <th>  
        #{@item[:info]}
      </th>
    </tr>
    " +
    if @user and !@user[:is_super]
    "
    <tr>
      <th>
        Действия:
      </th>
      <th>  
        <a href = 'aero.rb?controller=FlightTerminal&action=destroy&id=#{@item[:id]}'>Удалить</a> | 
      </th>
    </tr>
    "
    else
      ''
    end + 
    "
  </tbody>
</table>
"