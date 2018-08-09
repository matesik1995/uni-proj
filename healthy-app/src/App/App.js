import React, { Component } from 'react';
import Logo from '../Logo/Logo';
import Search from '../Search/Search';

class App extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className="app">
                <Logo />
                <Search />
            </div>
        );
    }
}

export default App;
