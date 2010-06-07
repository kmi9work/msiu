count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
  </caption>

  <thead>
    <tr>
      <th>
        Должность
      </th>
      <th>
        ФИО
      </th>
      <th>
        Возраст
      </th>
 <th>
        Действия
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{FlyPersonal::JOBS[i[:job_title]]}</td>
      <td>#{i[:first_name]}, #{i[:second_name]} #{i[:patronymic_name]}</td>
      <td>#{i[:age]}</td>
<td>
        <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{i[:id]}'>Редактировать</a>
        <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{i[:id]}'>Удалить</a>
      </td>     
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
