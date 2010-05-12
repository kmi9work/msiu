count = 0
"

<h2> #{@header} </h2>
<table class = 'list'>
"+
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
  <thead>
    <tr>
      <th>
        Номер рейса
      </th>
      <th>
        Вылет
      </th>
      <th>
        Посадка
      </th>
      <th>
        Авиакомпания
      </th>
      " +
      if @user and !@user[:is_super]
      "
      <th>
        Действия
      </th>
      "
      else
	''
      end +
      "
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td><a href ='aero.rb?controller=#{@controller}&action=show&id=#{i[:id]}'>#{i[:code]}</a></td>
      <td>#{i[:departure_place]}, #{i[:departure_airport]}: #{i[:departure_date]}</td>
      <td>#{i[:arrival_place]}, #{i[:arrival_airport]}: #{i[:arrival_date]}</td>
      <td>#{i.company_name()}</td>
      " +
      if @user and !@user[:is_super]
      "
        <td>
          <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{i[:id]}'>Редактировать</a>
          <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{i[:id]}'>Удалить</a>
        </td>
      "
      else
        ''  
      end + 
      "
    
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
