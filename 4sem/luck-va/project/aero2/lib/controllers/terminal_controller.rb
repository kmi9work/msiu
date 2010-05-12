class TerminalController < Controller
  def list
    @items = Terminal.find_all(@db)
    @header = 'Посадочные терминалы'
    render_template('list')
  end
  def edit
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params()
        if params.has_key?('id') and params['id'][0] != ''
          if @item.nil?
            @item = Terminal.new
            @header = 'Добавление терминала'
            @message = 'Терминал записан'
          else
            @item = Terminal.find_by_id(@db, params['id'][0])
            @header = 'Редактирование терминала'
            @message = 'Информация о терминале записана'
          end
        else
          @item = Terminal.new
          @header = 'Добавление терминала'
          @message = 'Терминал записан'
        end
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
      else
        if @cgi.params.has_key?('id')
          @item = Terminal.find_by_id(@db, @cgi.params['id'][0])
          if @item.nil?
            @item = Terminal.new
            @header = 'Добавление терминала'
          else
            @header = 'Редактирование терминала'
          end
        else
          @item = Terminal.new
          @header = 'Внесение новой информации о терминале'
        end
      end
      render_template('edit')
    else
      @message = 'У вас недостаточно прав'
      @link = 'controller=Terminal&action=list'
      render_template('error')
    end
  end
  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Terminal.find_by_id(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
end