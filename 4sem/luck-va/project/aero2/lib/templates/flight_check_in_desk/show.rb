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
        #{@item.check_in_desk[:name]}
      </th>  
    </tr>
    <tr>
      <th>
        Описание:
      </th>
      <th>  
        #{@item.check_in_desk[:description]}
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
        <a href = 'aero.rb?controller=FlightCheckInDesk&action=destroy&id=#{@item[:id]}'>Удалить</a> | 
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