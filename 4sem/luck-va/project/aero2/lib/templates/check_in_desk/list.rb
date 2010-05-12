count = 0
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
  <thead>
    <tr>
      <th>
        Название
      </th>
      <th>
        Описание
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
      <td>#{i[:name]}</td>
      <td>#{i[:description]}</td>
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
